#include "Mesh.h"

Mesh::Mesh()
	: position(0)
{

}

Mesh::Mesh(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

Mesh::~Mesh()
{

}

void Mesh::generateBlock(int x, int y, int z, float translate, float scale)
{
	GLfloat vertices[] = {
		//0
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, -1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, -1.0f, 0.0f,

		//3
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, -1.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z - 0.5f,		0.0f, -1.0f, 0.0f,

		//6
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, -1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 1.0f, 0.0f,

		//9
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 0.0f, -1.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z - 0.5f,		0.0f, 1.0f, 0.0f,

		//12
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, 1.0f,
		x - 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, -1.0f, 0.0f,

		//15
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, 1.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y - 0.5f * scale + translate), z + 0.5f,		0.0f, -1.0f, 0.0f,

		//18
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, 1.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		1.0f, 0.0f, 0.0f,
		x + 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 1.0f, 0.0f,

		//21
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		-1.0f, 0.0f, 0.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 0.0f, 1.0f,
		x - 0.5f, (y + 0.5f * scale + translate), z + 0.5f,		0.0f, 1.0f, 0.0f,
	};

	unsigned int indices[] = {
		4, 7, 19,	//PX
		19, 16, 4,
		21, 10, 1,	//NX
		1, 12, 21,
		11, 23, 20,	//PY
		20, 8, 11,
		17, 14, 2,	//NY
		2, 5, 17,
		22, 13, 15,	//PZ
		15, 18, 22,
		3, 0, 9,	//NZ
		9, 6, 3
	};
}
