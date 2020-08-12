#pragma once

#include <GL/glew.h>

class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shine);
	~Material();

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

