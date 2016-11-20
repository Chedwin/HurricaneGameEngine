#include "TitleScreenScene.h"
#include "SimulationScene.h"
#include <Debug.h>
#include <Game.h>
#include <InputHandler.h>

TitleScreenScene::TitleScreenScene() : countdownTime(0.0f)
{
	SetSceneName("Title Screen");
}

TitleScreenScene::~TitleScreenScene()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////

void TitleScreenScene::InitScene()
{
	Debug::ConsoleLog("Initializing Title Screen scene!");
}

void TitleScreenScene::Update(const hFLOAT _timeStep)
{
	countdownTime += _timeStep;

	if (countdownTime > 5.0f || INPUT->IsAnyKeyDown()) {
		Debug::ConsoleLog("This should switch to next scene!");

		Scene* sim = new SimulationScene();
		GAME->LoadScene(sim);
	}
}

void TitleScreenScene::Render()
{
	// Render stuff
}
