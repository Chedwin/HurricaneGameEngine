#include "Level.h"

Level::Level()
{
	//camera = new Camera(this);
}

Level::~Level()
{
	delete camera;
	camera = nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void Level::RenderLevel()
{
}

void Level::LevelRender()
{
}

void Level::LevelUpdate(const hFLOAT _timeStep)
{
}

void Level::SetCamera(Camera * _c)
{
}

void Level::LevelCleanUp()
{
}
