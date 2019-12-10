#include "Window.h"

Window::Window()
	:width(800), height(600), bufferHeight(0), bufferWidth(0), mainWindow(0)
{

}

Window::Window(GLint windowWidth, GLint windowHeight)
	:width(windowWidth), height(windowHeight), bufferHeight(0), bufferWidth(0), mainWindow(0)
{

}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}

int Window::Initialize()
{
	//Init GLFW
	if (!glfwInit())
	{
		printf("GLFW init failed");
		glfwTerminate();
		return 1;
	}

	//Setup GLFW window props
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Proccraft", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed");
		glfwTerminate();
		return 1;
	}

	//Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context for GLEW
	glfwMakeContextCurrent(mainWindow);

	//Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("GLEW init failed");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	//Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
	return 0;
}

GLfloat Window::getBufferWidth() 
{ 
	return (GLfloat)bufferWidth; 
}

GLfloat Window::getBufferHeight() 
{ 
	return (GLfloat)bufferHeight;
}

bool Window::getShouldClose() 
{ 
	return glfwWindowShouldClose(mainWindow); 
}

void Window::swapBuffers() 
{ 
	glfwSwapBuffers(mainWindow); 
}