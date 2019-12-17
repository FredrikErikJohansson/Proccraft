#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

#include "Block.h"

class Chunk
{
public:
	Chunk();
	~Chunk();

	void generateChunk(std::vector<Chunk*>& chunkList);
	void createChunk(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderChunk();
	void clearChunk();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

