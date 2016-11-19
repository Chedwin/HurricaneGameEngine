#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
}


SolarSystem::~SolarSystem()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL SolarSystem::InitGame()
{
	return true;
}

void SolarSystem::GameUpdate(const hFLOAT _deltaTime)
{
	STRINGSTREAM ss;
	ss << "Solar System Simulator 2016 | FPS: " << GetFPS();
	STRING fpsTitle = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), fpsTitle.c_str());
}

void SolarSystem::GameRender()
{
}

void SolarSystem::GameInput(SDL_Event & _evnt)
{
}
