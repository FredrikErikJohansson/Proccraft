#include "Block.h"

Block::Block()
	: position(0)
{

}

Block::Block(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

Block::~Block()
{

}

glm::vec3 Block::getPosition()
{
	return position;
}

std::vector<unsigned int> Block::getIndices()
{
	return indices;
}

std::vector<GLfloat> Block::getVertices()
{
	return vertices;
}

void Block::generateBlock(int x, int y, int z, std::vector<Block*>& blockList, float diff)
{
	//Create PX, NX, PY etc..
	float translate = -(diff / 2.0f) + 0.5f;
	float scale = diff;


	/*GLfloat px[] = {
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	1.0f, 0.0f, 0.0f,
	};

	GLfloat nx[] = {			
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	-1.0f, 0.0f, 0.0f,
	};

	GLfloat py[] = {
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	0.0f, 1.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	0.0f, 1.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	0.0f, 1.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	0.0f, 1.0f, 0.0f,
	};

	GLfloat ny[] = {
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	0.0f, -1.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	0.0f, -1.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	0.0f, -1.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	0.0f, -1.0f, 0.0f,
	};

	GLfloat pz[] = {
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	0.0f, 0.0f, 1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	0.0f, 0.0f, 1.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,	0.0f, 0.0f, 1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,	0.0f, 0.0f, 1.0f,
	};

	GLfloat nz[] = {
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	0.0f, 0.0f, -1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,	0.0f, 0.0f, -1.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	0.0f, 0.0f, -1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,	0.0f, 0.0f, -1.0f,
	};*/

	
	/*for (int i = 0; i < 24; i++)
	{
		PX.push_back(px[i]);
		NX.push_back(nx[i]);
		PY.push_back(py[i]);
		NY.push_back(ny[i]);
		PZ.push_back(pz[i]);
		NZ.push_back(nz[i]);
	}*/

	GLfloat vertices[] = {
		//0
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, 1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, -1.0f, 0.0f,

		//3
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, 1.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, -1.0f, 0.0f,

		//6
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, 1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 1.0f, 0.0f,

		//9
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, 1.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 1.0f, 0.0f,

		//12
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, -1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, -1.0f, 0.0f,

		//15
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, -1.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, -1.0f, 0.0f,

		//18
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, -1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 1.0f, 0.0f,

		//21
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, -1.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 1.0f, 0.0f,
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

	Block* block = new Block(x, y, z);
	blockList.push_back(block);
}
