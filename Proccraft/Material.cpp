#include "Material.h"

Material::Material()
	: specularIntensity(0), shininess(0)
{

}

Material::Material(GLfloat sIntensity, GLfloat shine)
	: specularIntensity(sIntensity), shininess(shine)
{

}

Material::~Material()
{

}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, shininess);
}