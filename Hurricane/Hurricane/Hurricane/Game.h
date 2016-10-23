//*******************************//
//
// Name:			Game.h
// Description:		Establishes a base application for all Hurricane games to derive from.
//
// Author:			Edwin Chen
// Created:			Jul 05, 2016
// Last updated:	Oct 12, 2016
//
//*******************************//
#pragma once

#ifndef GAME_H
#define GAME_H

#include "Hurricane.h"
#include "Camera.h"

#define GAME Game::GetGameInstance()
#define MAX_FPS 60.0f

class Game {
public:
	static Game* GetGameInstance();

	explicit Game();
	virtual ~Game();
	
	hBOOL InitSystems();
	void DestroySystems();

	hBOOL LoadLevel(Level* _level);
	
	void PreRender();
	void PostRender();


	void Run();
	void GameLoop();

	void EngineUpdate(const hFLOAT _timeStep);
	void EngineRender();

	// TO BE OVERLOADED BY THE DERIVED GAME
	virtual void GameUpdate(const hFLOAT _timeStep) {}
	virtual void GameRender() {}

	void CalculateFPS();

	// INLINE FUNCTIONS
	inline hBOOL IsGameRunning() const {
		return _isRunning;
	}

	inline void SetRunState(bool state) {
		_isRunning = state;
	}

	inline hFLOAT GetFPS() const {
		return fps;
	}

	inline hFLOAT GetTotalTime() const {
		return totalTime;
	}

protected:

	static Game* _gameInstance;

	Level* levelToLoad;

	hFLOAT fps;
	hFLOAT frameTime;

	hFLOAT totalTime, timeBetweenLastFrame, lastUpdateTime, timeSinceLastUpdate;
	hINT frames, timeSinceLastFPSUpdate;

	hBOOL _isRunning;
public:
	
	Camera* cam3D;

	Timer* gameTimer;
	
	HurricaneProperties* properties;
	AbstractRenderer* renderer;
	InputHandler* input;

	ModelManager*  modelManager;

	PhysicsEngine* physicsEngine;
	Level* currentLevel;
};

#endif