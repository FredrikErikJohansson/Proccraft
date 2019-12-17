#pragma once

#include <vector>
#include <math.h>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Block
{
public:
	Block();
	Block(float x, float y, float z);
	~Block();

	glm::vec3 getPosition();
	std::vector<unsigned int> getIndices();
	std::vector<GLfloat> getVertices();

	void generateBlock(int x, int y, int z, std::vector<Block*>& blockList, float diff);

private:
	glm::vec3 position;
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;
};

