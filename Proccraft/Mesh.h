#pragma once

#include <vector>
#include <math.h>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();
	Mesh(float x, float y, float z);
	~Mesh();

	void generateBlock(int x, int y, int z, float translate, float scale);

private:
	glm::vec3 position;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
};

