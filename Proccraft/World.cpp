#include "World.h"

World::World()
	: height(0)
{

}

World::~World()
{

}

void World::generateWorld(float xPos, float zPos, std::vector<Mesh*> &meshList)
{
	float y = 0;

	for (int x = xPos; x < 100 + xPos; x++)
	{
		for (int z = zPos; z < 100 + zPos; z++)
		{
			y = floor(10 * (glm::perlin(glm::vec2(x / 25.0f, z / 25.0f))));

			//Normals are in order front->left->back->right->up->down
			GLfloat vertices[] = {
				//0
				x + 0.0f, y + 0.0f, z + 0.0f,		0.0f, 0.0f, 1.0f,
				x + 0.0f, y + 0.0f, z + 0.0f,		-1.0f, 0.0f, 0.0f,
				x + 0.0f, y + 0.0f, z + 0.0f,		0.0f, -1.0f, 0.0f,

				//3
				x + 1.0f, y + 0.0f, z + 0.0f,		0.0f, 0.0f, 1.0f,
				x + 1.0f, y + 0.0f, z + 0.0f,		1.0f, 0.0f, 0.0f,
				x + 1.0f, y + 0.0f, z + 0.0f,		0.0f, -1.0f, 0.0f,

				//6
				x + 1.0f, y + 1.0f, z + 0.0f,		0.0f, 0.0f, 1.0f,
				x + 1.0f, y + 1.0f, z + 0.0f,		1.0f, 0.0f, 0.0f,
				x + 1.0f, y + 1.0f, z + 0.0f,		0.0f, 1.0f, 0.0f,

				//9
				x + 0.0f, y + 1.0f, z + 0.0f,		0.0f, 0.0f, 1.0f,
				x + 0.0f, y + 1.0f, z + 0.0f,		-1.0f, 0.0f, 0.0f,
				x + 0.0f, y + 1.0f, z + 0.0f,		0.0f, 1.0f, 0.0f,

				//12
				x + 0.0f, y + 0.0f, z + 1.0f,		-1.0f, 0.0f, 0.0f,
				x + 0.0f, y + 0.0f, z + 1.0f,		0.0f, 0.0f, -1.0f,
				x + 0.0f, y + 0.0f, z + 1.0f,		0.0f, -1.0f, 0.0f,

				//15
				x + 1.0f, y + 0.0f, z + 1.0f,		0.0f, 0.0f, -1.0f,
				x + 1.0f, y + 0.0f, z + 1.0f,		1.0f, 0.0f, 0.0f,
				x + 1.0f, y + 0.0f, z + 1.0f,		0.0f, -1.0f, 0.0f,

				//18
				x + 1.0f, y + 1.0f, z + 1.0f,		0.0f, 0.0f, -1.0f,
				x + 1.0f, y + 1.0f, z + 1.0f,		1.0f, 0.0f, 0.0f,
				x + 1.0f, y + 1.0f, z + 1.0f,		0.0f, 1.0f, 0.0f,

				//21
				x + 0.0f, y + 1.0f, z + 1.0f,		-1.0f, 0.0f, 0.0f,
				x + 0.0f, y + 1.0f, z + 1.0f,		0.0f, 0.0f, -1.0f,
				x + 0.0f, y + 1.0f, z + 1.0f,		0.0f, 1.0f, 0.0f,
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

			Mesh* obj01 = new Mesh();
			obj01->CreateMesh(vertices, indices, 144, 36);
			meshList.push_back(obj01);
		}
	}
}

float World::getHeight()
{
	return height;
}