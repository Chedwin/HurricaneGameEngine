//*******************************//
//
// Name:			GameSceneManager.h
// Description:		Handles scenes or levels throughout the game.
//					Inspired by the Unity scene structure.
//
// Author:			Edwin Chen
// Special thanks:  Scott Fielder
//
// Created:			Oct 01, 2015
// Last updated:	Nov 12, 2016
//
//*******************************//

#ifndef GAME_SCENE_MANAGER_H
#define GAME_SCENE_MANAGER_H

#include "Macro.h"
#include "ResourceManager.h"
#include "Scene.h"

#define SCENE_MANAGER GameSceneManager::GetSceneManager()

class GameSceneManager {
private:
	GameSceneManager();
	~GameSceneManager();

	void LoadScene(Scene* _scene);

private:
	static UNIQUE_PTR(GameSceneManager) _gameSceneInstance;
	friend DEFAULT_DELETE(GameSceneManager);
public:
	static GameSceneManager* GetSceneManager();

	Scene* currentScene;

	ResourceManager<Scene> sceneMap;
};

#endif