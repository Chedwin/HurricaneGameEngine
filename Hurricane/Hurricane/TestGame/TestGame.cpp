#include <FlyCamera.h>
#include <TextureManager.h>
#include <MaterialManager.h>
#include <ShaderProgramManager.h>
#include <HurricaneProperties.h>

#include "TestGame.h"
#include "TitleScreenScene.h"

TestGame::TestGame()
{
	_gameInstance = this;
}

TestGame::~TestGame()
{
	// Empty
}



/////////////////////////////////////////////////////////////////////////////////////////

hBOOL TestGame::InitGame()
{
	// Any pre-game init stuff?
	LoadScene(new TitleScreenScene());
	return true;
}


void TestGame::GameUpdate(const hFLOAT _deltaTime)
{
	STRING title = H_PROPERTIES->GetGeneralProperties()->gameName;

	STRING scene = currentScene->GetSceneName();

	// window title bar update
	STRINGSTREAM ss;
	ss << scene << " | " << title << " | FPS: " << GetFPS();
	//ss << "Test Game | FPS: " << GetFPS();
	STRING fpsTitle = ss.str();

	SDL_SetWindowTitle(gameWindow->GetWindow(), fpsTitle.c_str());
}

void TestGame::GameRender()
{
	// Probably should be empty...
}