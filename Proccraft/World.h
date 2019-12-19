#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Chunk.h"

class World
{
public:
	World();
	~World();

	void generateWorld(int xPos, int zPos, std::vector<Chunk*> & chunkList);
	float getHeight(); //Maybe not neccesary if we create blocks in this class

private:
	//void generateHeight(float xPos, float yPos);

	float height;
};

