#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity, GLfloat xdir, GLfloat yDir, GLfloat zDir);
	~DirectionalLight();

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);
	
private:
	glm::vec3 direction;
};

