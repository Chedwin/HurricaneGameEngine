//*******************************//
//
// Name:			Contoller.h
// Description:		Creates a controller abstracted class for 3rd party gamepads
//					For now there will only be allowed one controller per game
//					i.e. DualShock 4 or Xbox One conrollers
//
// Author:			Edwin Chen
// Created:			Mar 25, 2016
// Last updated:	Nov 05, 2016
//
//*******************************//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL.h>
#include "Macro.h"

enum CONTROLLER_RETURN {
	NEUTRAL = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SPACE
};

class Controller {
protected:

public:

	Controller();
	~Controller();

	void InitController();
	void ShutdownContoller();

	void ControllerUpdate(const float _deltaTime);
public:
	SDL_GameController* controller;
	CONTROLLER_RETURN controllerReturn;

	bool triggerSpace;
};

#endif