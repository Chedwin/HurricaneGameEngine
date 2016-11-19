//*******************************//
//
// Name:			Game.h
// Description:		Establishes a base application for all Hurricane games to derive from.
//
// Author:			Edwin Chen
// Created:			Jul 05, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#undef main


#include "Macro.h"
#include "Debug.h"
#include "Clock.h"
#include "Timer.h"

#include "Window.h"
#include "AbstractRenderer.h"

#include "HurricaneProperties.h"
#include "FPSCounter.h"

#include "InputHandler.h"
#include "AudioEngine.h"

#include "PhysicsEngine.h"

#include "Scene.h"


#define GAME Game::GetGameInstance()
#define MAX_FPS 60.0f

class Game {
private:
	void EngineUpdate(const hFLOAT _timeStep);
	void EngineRender();
public:

protected:
	explicit Game();

	// NOTE: Derived destructors will be called BEFORE this base Game destructor
	virtual ~Game();

	hBOOL InitEngine();
	virtual hBOOL InitGame() {
		return true;
	}
	void DestroySystems();

	hBOOL LoadScene(Scene* _scene);

	void PreRender();
	void PostRender();

public:
	static Game* GetGameInstance();

	void Run();
	void GameLoop();

	// TO BE OVERLOADED BY THE DERIVED GAME
	virtual void GameInput(SDL_Event& _evnt) {}
	virtual void GameUpdate(const hFLOAT _deltaTime) {}
	virtual void GameRender() {}


	// INLINE FUNCTIONS
	inline hBOOL IsGameRunning() const {
		return _isRunning;
	}

	inline void SetRunState(bool state) {
		_isRunning = state;
	}

	inline hFLOAT GetFPS() const {
		return _fps;
	}

	inline hFLOAT GetTotalTime() const {
		return totalTime;
	}
	inline hFLOAT GetDeltaTime() const {
		return _deltaTime;
	}

protected:
	static Game* _gameInstance;

	hFLOAT _fps;

	hFLOAT totalTime, lastUpdateTime, timeSinceLastUpdate;

	hBOOL _isRunning;
	hFLOAT _deltaTime;

	FPSCounter _fpsCounter;
public:

	Timer* gameTimer;
	Window* gameWindow;
	AbstractRenderer* renderer;

	HurricaneProperties* hProperties;
	InputHandler* input;
	AudioEngine* audio;

	Scene* currentScene;	
};

#endif