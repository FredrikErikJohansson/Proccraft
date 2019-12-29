#include "Chunk.h"
#include <iostream>

Chunk::Chunk()
	: VAO(0), VBO(0), IBO(0), indexCount(0), edgeVertices(4)
{

}

Chunk::~Chunk()
{
	clearChunk();
}

std::vector<GLfloat> Chunk::getEdgeVertices()
{
	return edgeVertices;
}

void Chunk::generateChunk(int xPos, int yPos, int zPos, std::vector<Chunk*>& chunkList)
{
	int counter = 0;
	const int size = 16;
	float amplitude = 10.0f;

	//Make it two voxels larger than the chunk in each axis
	std::vector<std::vector<std::vector<bool>>> blockMap(size + 2, std::vector<std::vector<bool>>(size + 2, std::vector<bool>(size + 2, false)));

	const int n = size * size * size * 144;
	const int m = size * size * size * 36;

	GLfloat* chunkVertices = new GLfloat[n];
	unsigned int* chunkIndices = new unsigned int[m];

	for (int x = xPos; x < size + xPos + 2; x++)
	{
		for (int y = yPos; y < size + yPos + 2; y++)
		{
			for (int z = zPos; z < size + zPos + 2; z++)
			{

				int posX = x - xPos;
				int posY = y - yPos;
				int posZ = z - zPos;

				int h = floor(amplitude * (glm::simplex(glm::vec3(x / 32.0f, y / 64.0f, z / 32.0f))));
				//h += floor(amplitude/2 * (glm::simplex(glm::vec3(x / 16.0f, y / 32.0f, z / 16.0f))));
				if (h > 0)
				{
					blockMap[posX][posY][posZ] = true;
				}	

				if (posX > 1 && posY > 1 && posZ > 1)
				{
					//Current block
					posX--;
					posY--;
					posZ--;

					if (!blockMap[posX][posY][posZ])
						continue;

					//TODO: Calculate normal with cross product
					GLfloat vertNX[] = {
						x - 0.5f, y + 0.5f, z - 0.5f,		-1.0f, 0.0f, 0.0f,
						x - 0.5f, y - 0.5f, z - 0.5f,		-1.0f, 0.0f, 0.0f,
						x - 0.5f, y - 0.5f, z + 0.5f,		-1.0f, 0.0f, 0.0f,
						x - 0.5f, y + 0.5f, z + 0.5f,		-1.0f, 0.0f, 0.0f,
					};

					GLfloat vertPX[] = {
						x + 0.5f, y - 0.5f, z + 0.5f,		1.0f, 0.0f, 0.0f,
						x + 0.5f, y - 0.5f, z - 0.5f,		1.0f, 0.0f, 0.0f,
						x + 0.5f, y + 0.5f, z - 0.5f,		1.0f, 0.0f, 0.0f,
						x + 0.5f, y + 0.5f, z + 0.5f,		1.0f, 0.0f, 0.0f,
					};

					GLfloat vertNY[] = {
						x + 0.5f, y - 0.5f, z - 0.5f,		0.0f, -1.0f, 0.0f,
						x + 0.5f, y - 0.5f, z + 0.5f,		0.0f, -1.0f, 0.0f,
						x - 0.5f, y - 0.5f, z + 0.5f,		0.0f, -1.0f, 0.0f,
						x - 0.5f, y - 0.5f, z - 0.5f,		0.0f, -1.0f, 0.0f,
					};

					GLfloat vertPY[] = {
						x - 0.5f, y + 0.5f, z + 0.5f,		0.0f, 1.0f, 0.0f,
						x + 0.5f, y + 0.5f, z + 0.5f,		0.0f, 1.0f, 0.0f,
						x + 0.5f, y + 0.5f, z - 0.5f,		0.0f, 1.0f, 0.0f,
						x - 0.5f, y + 0.5f, z - 0.5f,		0.0f, 1.0f, 0.0f,
					};

					GLfloat vertNZ[] = {
						x - 0.5f, y + 0.5f, z - 0.5f,		0.0f, 0.0f, -1.0f,
						x + 0.5f, y + 0.5f, z - 0.5f,		0.0f, 0.0f, -1.0f,
						x + 0.5f, y - 0.5f, z - 0.5f,		0.0f, 0.0f, -1.0f,
						x - 0.5f, y - 0.5f, z - 0.5f,		0.0f, 0.0f, -1.0f,
					};

					GLfloat vertPZ[] = {
						x + 0.5f, y - 0.5f, z + 0.5f,		0.0f, 0.0f, 1.0f,
						x + 0.5f, y + 0.5f, z + 0.5f,		0.0f, 0.0f, 1.0f,
						x - 0.5f, y + 0.5f, z + 0.5f,		0.0f, 0.0f, 1.0f,
						x - 0.5f, y - 0.5f, z + 0.5f,		0.0f, 0.0f, 1.0f,
					};

					unsigned int ind[] = {
						0, 1, 2,
						2, 3, 0
					};

					//Check all surrounding blocks
					if (!blockMap[posX - 1][posY][posZ])
					{
						std::copy(vertNX, vertNX + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}

					if (!blockMap[posX + 1][posY][posZ])
					{
						std::copy(vertPX, vertPX + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}

					if (!blockMap[posX][posY - 1][posZ])
					{
						std::copy(vertNY, vertNY + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}

					if (!blockMap[posX][posY + 1][posZ])
					{
						std::copy(vertPY, vertPY + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}

					if (!blockMap[posX][posY][posZ - 1])
					{
						std::copy(vertNZ, vertNZ + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}

					if (!blockMap[posX][posY][posZ + 1])
					{
						std::copy(vertPZ, vertPZ + 24, chunkVertices + 24 * counter);

						for (int i = 0; i < 6; i++)
							chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

						counter++;
					}
				}	
			}
		}
	}

	Chunk* chunk = new Chunk();
	chunk->createChunk(chunkVertices, chunkIndices, 24 * counter, 6 * counter);
	delete[] chunkVertices;
	delete[] chunkIndices;
	//std::copy(edges, edges + 4, chunk->edgeVertices.begin());
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