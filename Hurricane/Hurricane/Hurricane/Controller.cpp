#include "Controller.h"
#include "Debug.h"


Controller::Controller() {
	controller = nullptr;
	InitController();
}
Controller::~Controller() {
	ShutdownContoller();
}

void Controller::InitController() {
	for (int i = 0; i < SDL_NumJoysticks(); i++) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			std::cout << SDL_GameControllerMapping(controller) << std::endl;
			break;
		}
	}
	Debug::ConsoleLog("Controller has been initialized!");
} // end InitController()

void Controller::ShutdownContoller() {
	if (controller) {
		SDL_GameControllerClose(controller);
		controller = nullptr;
	}
}


void Controller::ControllerUpdate(const float _deltaTime) {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// up
	if (state[SDL_SCANCODE_W]) {
		//Debug::ConsoleLog("UP!");
		controllerReturn = UP;
	}
	// down
	else if (state[SDL_SCANCODE_S]) {
		//Debug::ConsoleLog("DOWN!");
		controllerReturn = DOWN;
	}
	// left
	else if (state[SDL_SCANCODE_A]) {
		//Debug::ConsoleLog("LEFT!");
		controllerReturn = LEFT;
	}
	// right
	else if (state[SDL_SCANCODE_D]) {
		//Debug::ConsoleLog("RIGHT!");
		controllerReturn = RIGHT;
	}
	else {
		controllerReturn = NEUTRAL;
	}


	if (state[SDL_SCANCODE_SPACE]) {
		//Debug::ConsoleLog("SHOOT!");
		//controllerReturn = SPACE;
		triggerSpace = true;
	}
	else {
		triggerSpace = false;
	}
}