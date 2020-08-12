#include "Light.h"

Light::Light()
	: color(1.0f), ambientIntensity(1.0f), diffuseIntensity(0.0f)
{
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
	: color(red, green, blue), ambientIntensity(aIntensity), diffuseIntensity(dIntensity)
{
}

Light::~Light()
{

}
