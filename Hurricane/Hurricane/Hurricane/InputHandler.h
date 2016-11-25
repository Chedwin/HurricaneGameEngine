//*******************************//
//
// Name:			InputHandler.h
// Description:		Defines handlers for several types of input devices.
//					i.e. keyboard, mouse, gamepad, etc.
//
// Author:			Edwin Chen
// Special Thanks:  
//
// Created:			Jul 17, 2016
// Last updated:	Nov 23, 2016
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


	void PressKey(SDL_Keycode keyid);
	void ReleaseKey(SDL_Keycode keyid);

	hBOOL IsKeyDown(SDL_Keycode key);
	hBOOL IsKeyPressed(SDL_Keycode key_);
	hBOOL IsKeyReleased(SDL_Keycode key_);
	hBOOL IsAnyKeyDown();

	void HitMouse(Uint8 key_);
	void ReleaseMouse(Uint8 key_);
	void SetMouseCoord(const hFLOAT x, const hFLOAT y);

	hBOOL IsMouseButtonDown(Uint8 button_);
	hBOOL IsMouseButtonPressed(Uint8 button_);
	hBOOL IsMouseButtonReleased(Uint8 button_);

private:
	static UNIQUE_PTR(InputHandler) _inputHandler;
	friend DEFAULT_DELETE(InputHandler);

protected:

	MAP(SDL_Keycode, hBOOL) _curKeyboardMap;
	MAP(SDL_Keycode, hBOOL) _oldKeyboardMap;

	MAP(Uint8, hBOOL) _curMouseMap;
	MAP(Uint8, hBOOL) _oldMouseMap;

	VEC2 _oldMousePos;
	VEC2 _curMousePos;
public:
	SDL_MouseMotionEvent motionEvent;
};

#endif