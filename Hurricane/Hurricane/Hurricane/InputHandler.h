//*******************************//
//
// Name:			InputHandler.h
// Description:		Defines handlers for several types of input devices.
//					i.e. keyboard, mouse, gamepad, etc.
//
// Author:			Edwin Chen
// Created:			Jul 17, 2016
// Last updated:	Sep 22, 2016
//
//*******************************//

#pragma once

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Macro.h"

#define INPUT InputHandler::GetInputHandler()

class InputHandler {
protected:
	InputHandler();
public:
	~InputHandler();

	static InputHandler* GetInputHandler();

	void Update();
	void TakeEvent(SDL_Event& _evnt);

private:
	static UNIQUE_PTR(InputHandler) _inputHandler;
	friend DEFAULT_DELETE(InputHandler);
};

#endif