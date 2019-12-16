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

void Chunk::generateChunk(std::vector<Chunk*>& chunkList)
{
	int counter = 0;
	int size = 8;
	std::vector<Block*> blockList;

	//GLfloat* resultVert = new GLfloat[144 * size * size * size];
	//unsigned int* resultInd = new unsigned int[36 * size * size * size];

	for (int x = 0; x < size; x++)
	{
		for (int z = 0; z < size; z++)
		{
			//float h = floor(20 * (glm::simplex(glm::vec2(x / 64.0f, z / 64.0f))));
			for (int y = 0; y < 2; y++)
			{
				//Generate whole chunk
				Block* block = new Block();
				block->generateBlock(x, y, z, blockList);
			}
		}
	}

	//Only send the vetices and faces needed
	//Check if there is a block in 6 neighbour sides
	//if true dont take that side
	//else use those vertices and indices for chunk
	//use the center of the block and check +1 in x, y and z

	std::vector<GLfloat> chunkVertices;
	std::vector<unsigned int> chunkIndices;	
	

	for (int i = 0; i < blockList.size(); i++)
	{
		Block* currentBlock = blockList.at(i);
		glm::vec3 blockPosI = currentBlock->getPosition();
		bool px = false, nx = false, py = false, ny = false, pz = false, nz = false;

		for (int j = 0; j < blockList.size(); j++)
		{
			
			//if (j == i) continue;

			glm::vec3 blockPosJ = blockList.at(j)->getPosition();

			//PX
			if (((blockPosI.x + 1) == blockPosJ.x) && (blockPosI.y == blockPosJ.y) && (blockPosI.z == blockPosJ.z)) 
				px = true;
			//NX
			if (((blockPosI.x - 1) == blockPosJ.x) && (blockPosI.y == blockPosJ.y) && (blockPosI.z == blockPosJ.z)) 
				nx = true;
			//PY
			if ((blockPosI.x == blockPosJ.x) && ((blockPosI.y + 1) == blockPosJ.y) && (blockPosI.z == blockPosJ.z)) 
				py = true;
			//NY
			if ((blockPosI.x == blockPosJ.x) && ((blockPosI.y - 1) == blockPosJ.y) && (blockPosI.z == blockPosJ.z)) 
				ny = true;
			//PZ
			if ((blockPosI.x == blockPosJ.x) && (blockPosI.y == blockPosJ.y) && ((blockPosI.z + 1) == blockPosJ.z)) 
				pz = true;
			//NZ
			if ((blockPosI.x == blockPosJ.x) && (blockPosI.y == blockPosJ.y) && ((blockPosI.z - 1) == blockPosJ.z)) 
				nz = true;

			//if (px || nx || py || ny || pz || nz)
				//std::cout << "hello" << std::endl;

			//Add visible vertices to chunk
			//Add 4 blockPosI vertices in its positiveX side (px) and their normals + indices
			if (!px) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getPX().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			} 
			if (!nx) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getNX().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			}
			if (!py) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getPY().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			}
			if (!ny) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getNY().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			}
			if (!pz) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getPZ().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			}
			if (!nz) {
				for (int k = 0; k < 24; k++) chunkVertices.push_back(currentBlock->getNZ().at(k));
				for (int k = 0; k < 6; k++) chunkIndices.push_back(currentBlock->getIndices().at(k) + 4 * counter);
				counter++;
			}
		}
	}

	int n = chunkVertices.size();
	int m = chunkIndices.size();
	GLfloat* a = &chunkVertices[0];
	unsigned int* b = &chunkIndices[0];


	Chunk* chunk = new Chunk();
	chunk->createChunk(a, b, n, m);
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
	glEnable(GL_CULL_FACE);
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