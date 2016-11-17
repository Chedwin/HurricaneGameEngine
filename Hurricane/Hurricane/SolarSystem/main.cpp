#include "Game.h"

class SolarSystem : public Game {
public:
	SolarSystem() {}
	~SolarSystem() {}

	//hBOOL InitGame() override { return true; }

	//void GameUpdate(const hFLOAT _deltaTime) override {}
	//void GameRender() override {}

	//void GameInput(SDL_Event& _evnt) override {}
};

int main(int agrc, char** argv) {

	SolarSystem ss;
	ss.Run();

	return 0;
}