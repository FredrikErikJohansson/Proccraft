#include "Chunk.h"
#include <iostream>

Chunk::Chunk()
	: VAO(0), VBO(0), IBO(0), indexCount(0)
{

}

Chunk::~Chunk()
{
	clearChunk();
}

void Chunk::generateChunk(int xPos, int zPos, std::vector<Chunk*>& chunkList)
{
	int counter = 0;
	const int size = 128;
	float amplitude = 40.0f;
	float scale = 0;

	const int n = size * size * 144;
	const int m = size * size * 36;

	GLfloat* chunkVertices = new GLfloat[n];
	unsigned int* chunkIndices = new unsigned int[m];

	for (int x = 0 + xPos; x < size + xPos; x++)
	{
		for (int z = 0 + zPos; z < size + zPos; z++)
		{
			//Layered noise functions to determine height
			float y = floor(amplitude * (glm::simplex(glm::vec2(x / 128.0f, z / 128.0f))));
			y += floor(amplitude/10.0f * (glm::simplex(glm::vec2(x / 16.0f, z / 16.0f))));

			scale = amplitude/5.0f;
			if (scale < 1.0f) scale = 1.0f;

			GLfloat vertices[] = {
				//0
				x - 0.5f, (y - 0.5f * scale), z - 0.5f,		0.0f, 0.0f, 1.0f,
				x - 0.5f, (y - 0.5f * scale), z - 0.5f,		-1.0f, 0.0f, 0.0f,
				x - 0.5f, (y - 0.5f * scale), z - 0.5f,		0.0f, -1.0f, 0.0f,

				//3
				x + 0.5f, (y - 0.5f * scale), z - 0.5f,		0.0f, 0.0f, 1.0f,
				x + 0.5f, (y - 0.5f * scale), z - 0.5f,		1.0f, 0.0f, 0.0f,
				x + 0.5f, (y - 0.5f * scale), z - 0.5f,		0.0f, -1.0f, 0.0f,

				//6
				x + 0.5f, (y + 0.5f * scale), z - 0.5f,		0.0f, 0.0f, 1.0f,
				x + 0.5f, (y + 0.5f * scale), z - 0.5f,		1.0f, 0.0f, 0.0f,
				x + 0.5f, (y + 0.5f * scale), z - 0.5f,		0.0f, 1.0f, 0.0f,

				//9
				x - 0.5f, (y + 0.5f * scale), z - 0.5f,		0.0f, 0.0f, 1.0f,
				x - 0.5f, (y + 0.5f * scale), z - 0.5f,		-1.0f, 0.0f, 0.0f,
				x - 0.5f, (y + 0.5f * scale), z - 0.5f,		0.0f, 1.0f, 0.0f,

				//12
				x - 0.5f, (y - 0.5f * scale), z + 0.5f,		-1.0f, 0.0f, 0.0f,
				x - 0.5f, (y - 0.5f * scale), z + 0.5f,		0.0f, 0.0f, -1.0f,
				x - 0.5f, (y - 0.5f * scale), z + 0.5f,		0.0f, -1.0f, 0.0f,

				//15
				x + 0.5f, (y - 0.5f * scale), z + 0.5f,		0.0f, 0.0f, -1.0f,
				x + 0.5f, (y - 0.5f * scale), z + 0.5f,		1.0f, 0.0f, 0.0f,
				x + 0.5f, (y - 0.5f * scale), z + 0.5f,		0.0f, -1.0f, 0.0f,

				//18
				x + 0.5f, (y + 0.5f * scale), z + 0.5f,		0.0f, 0.0f, -1.0f,
				x + 0.5f, (y + 0.5f * scale), z + 0.5f,		1.0f, 0.0f, 0.0f,
				x + 0.5f, (y + 0.5f * scale), z + 0.5f,		0.0f, 1.0f, 0.0f,

				//21
				x - 0.5f, (y + 0.5f * scale), z + 0.5f,		-1.0f, 0.0f, 0.0f,
				x - 0.5f, (y + 0.5f * scale), z + 0.5f,		0.0f, 0.0f, -1.0f,
				x - 0.5f, (y + 0.5f * scale), z + 0.5f,		0.0f, 1.0f, 0.0f,
			};

			unsigned int indices[] = {
				0, 3, 6,	//Front
				6, 9, 0,
				12, 1, 10,	//Left
				10, 21, 12,
				15, 13, 22,	//Back
				22, 18, 15,
				4, 16, 19,	//Right
				19, 7, 4,
				11, 8, 20,	//Up
				20, 23, 11,
				14, 17, 5,	//Down
				5, 2, 14
			};



			for (int i = 0; i < 144; i++)
				chunkVertices[i + 144 * counter] = vertices[i];

			for (int i = 0; i < 36; i++)
				chunkIndices[i + 36*counter] = indices[i] + 24*counter;

			counter++;
		}
	}

	Chunk* chunk = new Chunk();
	chunk->createChunk(chunkVertices, chunkIndices, n, m);
	chunkList.push_back(chunk);
}

void Chunk::createChunk(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
	indexCount = numOfIndices;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 6, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Chunk::renderChunk()
{
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Chunk::clearChunk()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}