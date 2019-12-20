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
	const int size = 64;
	float amplitude = 40.0f;

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
				if (floor(amplitude * (glm::simplex(glm::vec3(x / 128.0f, y / 128.0f, z / 128.0f)))) > 0.0f)
					blockMap[x - xPos][y - yPos][z - zPos] = true;
			}
		}
	}

	for (int x = xPos; x < size + xPos; x++)
	{
		for (int y = yPos; y < size + yPos; y++)
		{
			for (int z = zPos; z < size + zPos; z++)
			{
				int posX = x - xPos + 1;
				int posY = y - yPos + 1;
				int posZ = z - zPos + 1;

				if (!blockMap[posX][posY][posZ])
					continue;

				GLfloat vertNX[] = {
					x - 0.5f, (y + 0.5f), z - 0.5f,		-1.0f, 0.0f, 0.0f,
					x - 0.5f, (y - 0.5f), z - 0.5f,		-1.0f, 0.0f, 0.0f,
					x - 0.5f, (y - 0.5f), z + 0.5f,		-1.0f, 0.0f, 0.0f,
					x - 0.5f, (y + 0.5f), z + 0.5f,		-1.0f, 0.0f, 0.0f,					
				};

				GLfloat vertPX[] = {
					x + 0.5f, (y - 0.5f), z + 0.5f,		1.0f, 0.0f, 0.0f,
					x + 0.5f, (y - 0.5f), z - 0.5f,		1.0f, 0.0f, 0.0f,
					x + 0.5f, (y + 0.5f), z - 0.5f,		1.0f, 0.0f, 0.0f,
					x + 0.5f, (y + 0.5f), z + 0.5f,		1.0f, 0.0f, 0.0f,			
				};

				GLfloat vertNY[] = {
					x + 0.5f, (y - 0.5f), z - 0.5f,		0.0f, -1.0f, 0.0f,
					x + 0.5f, (y - 0.5f), z + 0.5f,		0.0f, -1.0f, 0.0f,
					x - 0.5f, (y - 0.5f), z + 0.5f,		0.0f, -1.0f, 0.0f,
					x - 0.5f, (y - 0.5f), z - 0.5f,		0.0f, -1.0f, 0.0f,							
				};

				GLfloat vertPY[] = {
					x - 0.5f, (y + 0.5f), z + 0.5f,		0.0f, 1.0f, 0.0f,
					x + 0.5f, (y + 0.5f), z + 0.5f,		0.0f, 1.0f, 0.0f,
					x + 0.5f, (y + 0.5f), z - 0.5f,		0.0f, 1.0f, 0.0f,
					x - 0.5f, (y + 0.5f), z - 0.5f,		0.0f, 1.0f, 0.0f,				
				};

				GLfloat vertNZ[] = {
					x - 0.5f, (y + 0.5f), z - 0.5f,		0.0f, 0.0f, -1.0f,
					x + 0.5f, (y + 0.5f), z - 0.5f,		0.0f, 0.0f, -1.0f,
					x + 0.5f, (y - 0.5f), z - 0.5f,		0.0f, 0.0f, -1.0f,
					x - 0.5f, (y - 0.5f), z - 0.5f,		0.0f, 0.0f, -1.0f,	
				};

				GLfloat vertPZ[] = {
					x + 0.5f, (y - 0.5f), z + 0.5f,		0.0f, 0.0f, 1.0f,
					x + 0.5f, (y + 0.5f), z + 0.5f,		0.0f, 0.0f, 1.0f,
					x - 0.5f, (y + 0.5f), z + 0.5f,		0.0f, 0.0f, 1.0f,
					x - 0.5f, (y - 0.5f), z + 0.5f,		0.0f, 0.0f, 1.0f,				
				};

				unsigned int ind[] = {
					0, 1, 2,
					2, 3, 0
				};

				//Check all surrounding blocks
				if (!blockMap[posX - 1][posY][posZ])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertNX[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;			
				}

				if (!blockMap[posX + 1][posY][posZ])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertPX[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;
				}

				if (!blockMap[posX][posY - 1][posZ])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertNY[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;
				}

				if (!blockMap[posX][posY + 1][posZ])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertPY[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;
				}

				if (!blockMap[posX][posY][posZ - 1])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertNZ[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;
				}

				if (!blockMap[posX][posY][posZ + 1])
				{
					for (int i = 0; i < 24; i++)
						chunkVertices[i + 24 * counter] = vertPZ[i];

					for (int i = 0; i < 6; i++)
						chunkIndices[i + 6 * counter] = ind[i] + 4 * counter;

					counter++;
				}

				

				/*GLfloat vert[] = {
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

				unsigned int ind[] = {
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

				//Store edge vertices
				if (vert[0] < edges[1]) edges[1] = vert[0];
				if (vert[2] < edges[3]) edges[3] = vert[2];
				if (vert[18] > edges[0]) edges[0] = vert[18];
				if (vert[74] > edges[2]) edges[2] = vert[74];


				for (int i = 0; i < 144; i++)
					chunkVertices[i + 144 * counter] = vert[i];

				for (int i = 0; i < 36; i++)
					chunkIndices[i + 36 * counter] = ind[i] + 24 * counter;

				counter++; */
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
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
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