#include <SDL.h>
#undef main

#include <Macro.h>
#include <Controller.h>
#include <ControllerManager.h>
#include "TestGame.h"
#include "NewGame.h"

int main(int argc, char** argv) {
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	//TestGame test;
	//test.Run();

	NewGame newGame;
	newGame.Run();

	return 0;
}