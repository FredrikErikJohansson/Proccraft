#include "Block.h"

Block::Block()
	: position(0)
{

}

Block::Block(float x, float y, float z, std::vector<GLfloat> _PX, std::vector<GLfloat> _NX, std::vector<GLfloat> _PY, std::vector<GLfloat> _NY, std::vector<GLfloat> _PZ, std::vector<GLfloat> _NZ)
{
	position = glm::vec3(x, y, z);
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
	PX = _PX;
	NX = _NX;
	PY = _PY;
	NY = _NY;
	PZ = _PZ;
	NZ = _NZ;
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

std::vector<GLfloat> Block::getPX()
{
	return PX;
}

std::vector<GLfloat> Block::getNX()
{
	return NX;
}

std::vector<GLfloat> Block::getPY()
{
	return PY;
}

std::vector<GLfloat> Block::getNY()
{
	return NY;
}

std::vector<GLfloat> Block::getPZ()
{
	return PZ;
}

std::vector<GLfloat> Block::getNZ()
{
	return NZ;
}

void Block::generateBlock(int x, int y, int z, std::vector<Block*>& blockList)
{
	//Create PX, NX, PY etc..
	GLfloat px[] = {
		x + 0.5f, y - 0.5f, z + 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, y - 0.5f, z - 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, y + 0.5f, z - 0.5f,	1.0f, 0.0f, 0.0f,
		x + 0.5f, y + 0.5f, z + 0.5f,	1.0f, 0.0f, 0.0f,	
	};

	GLfloat nx[] = {			
		x - 0.5f, y + 0.5f, z + 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, y + 0.5f, z - 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, y - 0.5f, z - 0.5f,	-1.0f, 0.0f, 0.0f,
		x - 0.5f, y - 0.5f, z + 0.5f,	-1.0f, 0.0f, 0.0f,		
	};

	GLfloat py[] = {
		x - 0.5f, y + 0.5f, z - 0.5f,	0.0f, 1.0f, 0.0f,
		x - 0.5f, y + 0.5f, z + 0.5f,	0.0f, 1.0f, 0.0f,
		x + 0.5f, y + 0.5f, z + 0.5f,	0.0f, 1.0f, 0.0f,
		x + 0.5f, y + 0.5f, z - 0.5f,	0.0f, 1.0f, 0.0f,	
	};

	GLfloat ny[] = {
		x + 0.5f, y - 0.5f, z + 0.5f,	0.0f, -1.0f, 0.0f,
		x - 0.5f, y - 0.5f, z + 0.5f,	0.0f, -1.0f, 0.0f,
		x - 0.5f, y - 0.5f, z - 0.5f,	0.0f, -1.0f, 0.0f,
		x + 0.5f, y - 0.5f, z - 0.5f,	0.0f, -1.0f, 0.0f,	
	};

	GLfloat pz[] = {
		x - 0.5f, y + 0.5f, z + 0.5f,	0.0f, 0.0f, 1.0f,
		x - 0.5f, y - 0.5f, z + 0.5f,	0.0f, 0.0f, 1.0f,
		x + 0.5f, y - 0.5f, z + 0.5f,	0.0f, 0.0f, 1.0f,
		x + 0.5f, y + 0.5f, z + 0.5f,	0.0f, 0.0f, 1.0f,	
	};

	GLfloat nz[] = {
		x + 0.5f, y - 0.5f, z - 0.5f,	0.0f, 0.0f, -1.0f,
		x - 0.5f, y - 0.5f, z - 0.5f,	0.0f, 0.0f, -1.0f,
		x - 0.5f, y + 0.5f, z - 0.5f,	0.0f, 0.0f, -1.0f,
		x + 0.5f, y + 0.5f, z - 0.5f,	0.0f, 0.0f, -1.0f,	
	};

	
	for (int i = 0; i < 24; i++)
	{
		PX.push_back(px[i]);
		NX.push_back(nx[i]);
		PY.push_back(py[i]);
		NY.push_back(ny[i]);
		PZ.push_back(pz[i]);
		NZ.push_back(nz[i]);
	}

	Block* block = new Block(x, y, z, PX, NX, PY, NY, PZ, NZ);
	blockList.push_back(block);
}
