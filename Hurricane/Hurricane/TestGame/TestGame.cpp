#include "TestGame.h"


TestGame::TestGame() 
{
	_gameInstance = this;
}

TestGame::~TestGame() {

}

void TestGame::GameRender()
{
	renderer->Render();
}

void TestGame::GameUpdate(const hFLOAT _deltatime)
{
	STRINGSTREAM ss;
	ss << "Pong | FPS: " << fps;
	STRING _fps = ss.str();

	SDL_SetWindowTitle(renderer->GetWindow(), _fps.c_str());
}
