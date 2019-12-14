#include <stdio.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "World.h"

#include <glm/gtc/noise.hpp>

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;
World world;

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
	glEnable(GL_CULL_FACE);
	mainWindow = Window(960, 540);
	mainWindow.Initialize();

	world.generateWorld(0.0f, 0.0f, meshList);

	//CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.2f);

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f, 2.5f, 3.0f, -2.0f, 1.0f);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColor = 0, uniformDiffuseIntensity = 0, uniformDirection = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();
		uniformDirection = shaderList[0]->GetDirectionLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

		glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, increment * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		for (int i = 0; i < 10000; i++)
		{
			meshList[i]->RenderMesh();
		}


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
