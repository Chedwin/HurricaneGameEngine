//*******************************//
//
// Name:			SolarSystem.h
// Description:		Define solar system game from OpenGL class.
//
// Author:			Edwin Chen
// Created:			Nov 17, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//

#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include "Game.h"

class SolarSystem : public Game {
public:
	SolarSystem();
	~SolarSystem();

	hBOOL InitGame() override;

	void GameUpdate(const hFLOAT _deltaTime) override;
	void GameRender() override;

	void GameInput(SDL_Event& _evnt) override;

public:
};

#endif