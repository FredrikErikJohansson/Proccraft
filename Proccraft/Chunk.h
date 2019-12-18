#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <string>

#include "Block.h"

class Chunk
{
public:
	Chunk();
	~Chunk();

	void generateChunk(int xPos, int zPos, std::vector<Chunk*>& chunkList, float* lastHeightPX, float* lastHeightNX, float* lastHeightPZ, float* lastHeightNZ);
	void createChunk(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderChunk();
	void clearChunk();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};
