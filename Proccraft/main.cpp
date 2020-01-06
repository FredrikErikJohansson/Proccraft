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
#include "Light.h"
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

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	//TODO: Generate veritces to create heightmap
	//Maybe do it in a class and then draw it as a batch

}

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

	int nbFrames = 0;
	double lT = glfwGetTime();
	const int cSize = 16;
	int counter = 0;

	std::vector<std::vector<std::vector<bool>>> worldMap(64, std::vector<std::vector<bool>>(64, std::vector<bool>(64, false)));
		
	//CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 10.0f, 0.2f);

	//shinyMaterial = Material(1.0f, 32.0f);
	dullMaterial = Material(0.3f, 4.0f);

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.5f, 2.5f, 3.0f, -2.0f, 0.5f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	GLuint uniformAmbientIntensity = 0, uniformEyePosition = 0;
	GLuint uniformAmbientColor = 0, uniformDiffuseIntensity = 0, uniformDirection = 0;
	GLuint uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	//Render
	while (!mainWindow.getShouldClose())
	{
		GLfloat currentTime = (GLfloat)glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Measure speed
		nbFrames++;

		if (currentTime - lT >= 0.1 && renderQueue.size() > 0)
		{
			chunkList.push_back(*renderQueue.begin());
			renderQueue.erase(renderQueue.begin());
		}

		if (currentTime - lT >= 1.0) { // If last prinf() was more than 1 sec ago
			// printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lT += 1.0;	
		}


		//Handle input events
		glfwPollEvents();
		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Clear window
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();
		uniformDirection = shaderList[0]->GetDirectionLocation();
		uniformEyePosition = shaderList[0]->GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model(1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		int coordX = (int)floor(camera.getCameraPosition().x / 16);
		int coordY = (int)floor(camera.getCameraPosition().y / 16);
		int coordZ = (int)floor(camera.getCameraPosition().z / 16);

		for (int x = coordX - 2; x < coordX + 2; x++)
		{
			for (int y = coordY - 2; y < coordY + 2; y++)
			{
				for (int z = coordZ - 2; z < coordZ + 2; z++)
				{
					if (x >= -32 && x < 32 && y >= -32 && y < 32 && z >= -32 && z < 32)
					{
						if (!worldMap[x + 32][y + 32][z + 32])
							chunk.generateChunk(x * cSize, y * cSize, z * cSize, renderQueue);
							
						worldMap[x + 32][y + 32][z + 32] = true;
					}			
				}
			}
		}

		for (size_t i = 0; i < chunkList.size(); i++)
			chunkList[i]->renderChunk();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
