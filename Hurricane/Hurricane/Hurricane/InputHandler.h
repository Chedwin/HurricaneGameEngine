//*******************************//
//
// Name:			InputHandler.h
// Description:		Defines handlers for several types of input devices.
//					i.e. keyboard, mouse, gamepad, etc.
//
// Author:			Edwin Chen
// Created:			Jul 17, 2016
// Last updated:	Nov 14, 2016
//
//*******************************//


#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL.h>
#include "Macro.h"
#include "HMath.h"

#define INPUT InputHandler::GetInputHandler()

class InputHandler {
protected:
	InputHandler();
public:
	~InputHandler();

	static InputHandler* GetInputHandler();

	void Update();

	void ProcessInput(SDL_Event& _evnt);

	void PressKey(hUINT keyid);
	void ReleaseKey(hUINT keyid);

	hBOOL IsKeyDown(hUINT key);

	VEC2 mousePos;

private:
	static UNIQUE_PTR(InputHandler) _inputHandler;
	friend DEFAULT_DELETE(InputHandler);

	UNORDERED_MAP(hUINT, hBOOL) _keyMap;
};

#endif