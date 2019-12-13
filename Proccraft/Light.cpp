#include "Light.h"

Light::Light()
	: color(1.0f), ambientIntensity(1.0f), diffuseIntensity(0.0f)
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xdir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
	: color(red, green, blue), ambientIntensity(aIntensity), diffuseIntensity(dIntensity)
{
	direction = glm::vec3(xdir, yDir, zDir);
}

Light::~Light()
{

}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, GLuint directionLocation)
{
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

