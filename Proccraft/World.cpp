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

void World::generateWorld(float xPos, float zPos, std::vector<Chunk*> & chunkList)
{
	Chunk* chunk = new Chunk();
	chunk->generateChunk(chunkList);
}

float World::getHeight()
{
	return height;
}