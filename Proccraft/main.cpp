#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Chunk.h"
#include "Shader.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "Material.h"

#include <glm/gtc/noise.hpp>

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Chunk*> chunkList;
std::vector<Shader*> shaderList;
std::vector<Chunk*> renderQueue;
Camera camera;
Chunk chunk;

Material shinyMaterial;
Material dullMaterial;

DirectionalLight mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

void CreateShaders()
{
	Shader* shader01 = new Shader();
	shader01->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader01);
}

int main()
{
	mainWindow = Window(960, 540);
	mainWindow.Initialize();

	double lT = glfwGetTime();
	const int cSize = 16;
	const int wSize = 256;
	int counter = 0;

	//Customizable
	int viewDist = 3;
	float xNoise = 30.0f;
	float yNoise = 40.0f;
	float zNoise = 30.0f;
	float amplitude = 10.0f;

	std::vector<std::vector<std::vector<bool>>> worldMap(wSize, std::vector<std::vector<bool>>(wSize, std::vector<bool>(wSize, false)));
		
	//CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(-10.0f, 10.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 8.0f, 0.2f);

	//shinyMaterial = Material(1.0f, 32.0f);
	dullMaterial = Material(0.3f, 4.0f);

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 2.5f, -3.0f, -2.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GLuint uniformEyePosition = 0;
	GLuint uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	//Render
	while (!mainWindow.getShouldClose())
	{
		GLfloat currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (currentTime - lT >= 0.1 && renderQueue.size() > 0)
		{
			chunkList.push_back(renderQueue.back());
			renderQueue.pop_back();
		}

		//Handle input events
		glfwPollEvents();
		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		if (mainWindow.getKeys()[GLFW_KEY_R])
			glfwSetInputMode(mainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		if (mainWindow.getKeys()[GLFW_KEY_F])
			glfwSetInputMode(mainWindow.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//Clear window
		glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformEyePosition = shaderList[0]->GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();

		shaderList[0]->SetDirectionalLight(&mainLight);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		int coordX = (int)floor(camera.getCameraPosition().x / 16);
		int coordY = (int)floor(camera.getCameraPosition().y / 16);
		int coordZ = (int)floor(camera.getCameraPosition().z / 16);

		//View distance = 5, render 5^2 chunks for every camera movement of 16 voxels
		for (int x = coordX - (viewDist-1); x < coordX + viewDist; x++)
		{
			for (int y = coordY - (viewDist-1); y < coordY + viewDist; y++)
			{
				for (int z = coordZ - (viewDist-1); z < coordZ + viewDist; z++)
				{
					if (x >= -(wSize/2) && x < (wSize / 2) && y >= -(wSize / 2) && y < (wSize / 2) && z >= -(wSize / 2) && z < (wSize / 2))
					{
						if (!worldMap[x + (wSize / 2)][y + (wSize / 2)][z + (wSize / 2)])
							chunk.generateChunk(x * cSize, y * cSize, z * cSize, renderQueue, xNoise, yNoise, zNoise, amplitude);

						worldMap[x + (wSize / 2)][y + (wSize / 2)][z + (wSize / 2)] = true;	
					}			
				}
			}
		}

		for (size_t i = 0; i < chunkList.size(); i++)
			chunkList[i]->renderChunk();


		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Proccraft");
		ImGui::Text("Press 'R' to enable cursor");
		ImGui::Text("Press 'F' to disable cursor");
		ImGui::InputInt("View distance", &viewDist, 2);
		ImGui::SliderFloat("Camera speed", camera.getMovementSpeed(), 1.0f, 40.0f);
		ImGui::SliderFloat("Noise freq X", &xNoise, 8.0f, 128.0f);
		ImGui::SliderFloat("Noise freq Y", &yNoise, 8.0f, 128.0f);
		ImGui::SliderFloat("Noise freq Z", &zNoise, 8.0f, 128.0f);
		ImGui::SliderFloat("Noise ampltude", &amplitude, 2.0f, 30.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
