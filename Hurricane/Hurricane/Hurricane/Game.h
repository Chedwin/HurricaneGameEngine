//*******************************//
//
// Name:			Game.h
// Description:		Establishes a base application for all Hurricane games to derive from.
//
// Author:			Edwin Chen
// Created:			May 02, 2016
// Last updated:	Nov 18, 2016
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
protected:
	explicit Game();

	// NOTE: Derived destructors will be called BEFORE this base Game destructor
	virtual ~Game();

	hBOOL InitEngine();
	virtual hBOOL InitGame() {
		return true;
	}
	void DestroySystems();


	void PreRender();
	void PostRender();

public:
	static Game* GetGameInstance();

	void Run();
	void GameLoop();
	void LoadScene(Scene* _scene);

	// TO BE OVERLOADED BY THE DERIVED GAME
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
		return _totalTime;
	}
	inline hFLOAT GetDeltaTime() const {
		return _deltaTime;
	}

protected:
	static Game* _gameInstance;

	hFLOAT _fps;

	hFLOAT _totalTime, _lastUpdateTime, _timeSinceLastUpdate;

	hBOOL _isRunning;
	hBOOL _canLoadNewScene;
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
	Scene* sceneToLoad;
};

#endif