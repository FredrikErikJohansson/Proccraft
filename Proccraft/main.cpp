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

	int stupidTimerX = 0;
	int stupidTimerZ = 0;
	int stupidTimerNX = 0;
	int stupidTimerNZ = 0;

	const int wSize = 256;
	const int cSize = 64;
	const int side = (wSize / cSize);

	int PX = 0;
	int PZ = 0;
	int NX = 0;
	int NZ = 0;

	int counter = 0;
	bool inside = true;

	/*while (PX < wSize)
	{
		while (PZ < wSize)
		{
			chunk.generateChunk(PX, 0.0f, PZ, chunkList);
			PZ += cSize;
			counter++;
		}
		PX += cSize;
		PZ = NZ;
	}*/

	chunk.generateChunk(0.0f, 0.0f, 0.0f, chunkList);
	chunk.generateChunk((float)cSize, 0.0f, 0.0f, chunkList);
		

	//CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 50.0f, 0.2f);

	//shinyMaterial = Material(1.0f, 32.0f);
	dullMaterial = Material(0.3f, 4.0f);

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f, 2.5f, 3.0f, -2.0f, 0.3f);

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

		//Handle input events
		glfwPollEvents();
		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//Clear window
		glClearColor(0.0f, 0.6f, 1.0f, 1.0f);
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
		model = glm::translate(model, glm::vec3(0.0f, -10.0f, -0.0f));
		//model = glm::rotate(model, increment * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		//printf("Camera: %f , %f, %f \n", camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		for(size_t i = 0; i < chunkList.size(); i++)
			chunkList[i]->renderChunk();

		if ((int)floor(camera.getCameraPosition().z) % cSize == 0) stupidTimerZ++;
		else if ((int)floor(camera.getCameraPosition().x) % cSize == 0) stupidTimerX++;
		else
		{
			stupidTimerX = 0;
			stupidTimerZ = 0;
		}


		//TODO: Add flag to only run this once
		/*if (stupidTimerZ == 1 && (int)floor(camera.getCameraPosition().z) % cSize/2 == 0)
		{
			//Sort by PZ ascending
			std::sort(chunkList.begin(), chunkList.end(), [](const Chunk* lhs, const Chunk* rhs)
			{
				return lhs->edgeVertices[2] < rhs->edgeVertices[2];
			});

			for (int i = 0; i < side; i++)
				delete chunkList[i];

			if(chunkList.size() == counter)
				chunkList.erase(chunkList.begin(), chunkList.begin() + side);
		
			for (int i = 0; i < side; i++)
				chunk.generateChunk(PX - cSize * i, PZ, chunkList);

			PZ += cSize;
			NZ += cSize;
		}

		if (stupidTimerX == 1 && (int)floor(camera.getCameraPosition().x) % cSize/2 == 0)
		{
			//Sort by PX ascending
			std::sort(chunkList.begin(), chunkList.end(), [](const Chunk* lhs, const Chunk* rhs)
			{
				return lhs->edgeVertices[0] < rhs->edgeVertices[0];
			});

			for (int i = 0; i < side; i++)
				delete chunkList[i];

			if (chunkList.size() == counter)
				chunkList.erase(chunkList.begin(), chunkList.begin() + side);

			for (int i = 0; i < side; i++)
				chunk.generateChunk(PX, NZ + cSize * i, chunkList);

			PX += cSize;
			NX += cSize;
		}*/

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
