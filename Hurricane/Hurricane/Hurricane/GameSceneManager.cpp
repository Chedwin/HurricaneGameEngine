#include "GameSceneManager.h"

UNIQUE_PTR(GameSceneManager) GameSceneManager::_gameSceneInstance(nullptr);

GameSceneManager* GameSceneManager::GetSceneManager() {
	if (_gameSceneInstance.get() == nullptr) {
		_gameSceneInstance.reset(new GameSceneManager());
	}
	return _gameSceneInstance.get();
}


GameSceneManager::GameSceneManager() 
{
	// EMPTY
}
GameSceneManager::~GameSceneManager()
{
	// EMPTY
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameSceneManager::LoadScene(Scene * _scene)
{
	currentScene = _scene;
}