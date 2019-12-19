#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

#include <vector>

class Chunk
{
public:
	Chunk();
	~Chunk();

	std::vector<GLfloat> getEdgeVertices();

	void generateChunk(int xPos, int zPos, std::vector<Chunk*>& chunkList);
	void createChunk(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void renderChunk();
	void clearChunk();

	//TODO: Move to private (used in lambda)
	std::vector<GLfloat> edgeVertices;

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

