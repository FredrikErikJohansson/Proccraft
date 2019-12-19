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

void World::generateWorld(int xPos, int zPos, std::vector<Chunk*> & chunkList)
{

	Chunk* chunk = new Chunk();
	chunk->generateChunk(xPos, zPos, chunkList);

}

float World::getHeight()
{
	return height;
}