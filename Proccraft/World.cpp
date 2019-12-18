#include "World.h"
#include <iostream>
#include <algorithm>

World::World()
	: height(0)
{

}

World::~World()
{

}

void World::generateWorld(int xPos, int zPos, std::vector<Chunk*> & chunkList, float* lastHeightPX, float* lastHeightNX, float* lastHeightPZ, float* lastHeightNZ)
{

	Chunk* chunk = new Chunk();
	chunk->generateChunk(xPos, zPos, chunkList, lastHeightPX, lastHeightNX, lastHeightPZ, lastHeightNZ);

}

float World::getHeight()
{
	return height;
}