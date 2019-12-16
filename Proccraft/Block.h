#pragma once

#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

class Block
{
public:
	Block();
	Block(float x, float y, float z, std::vector<GLfloat> _PX, std::vector<GLfloat> _NX, std::vector<GLfloat> _PY, std::vector<GLfloat> _NY, std::vector<GLfloat> _PZ, std::vector<GLfloat> _NZ);
	~Block();

	glm::vec3 getPosition();
	std::vector<unsigned int> getIndices();
	std::vector<GLfloat> getPX();
	std::vector<GLfloat> getNX();
	std::vector<GLfloat> getPY();
	std::vector<GLfloat> getNY();
	std::vector<GLfloat> getPZ();
	std::vector<GLfloat> getNZ();

	void generateBlock(int x, int y, int z, std::vector<Block*>& blockList);

private:
	glm::vec3 position;
	std::vector<GLfloat> PX;
	std::vector<GLfloat> NX;
	std::vector<GLfloat> PY;
	std::vector<GLfloat> NY;
	std::vector<GLfloat> PZ;
	std::vector<GLfloat> NZ;
	std::vector<unsigned int> indices;
};

