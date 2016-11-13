#include "InputHandler.h"
#include "Debug.h"
#include "Game.h"

UNIQUE_PTR(InputHandler) InputHandler::_inputHandler(nullptr);

InputHandler* InputHandler::GetInputHandler() 
{
	if (_inputHandler.get() == nullptr) 
	{
		/// I originally set the unique_ptr to be null in the constructor - reset() sets the new address
		_inputHandler.reset(new InputHandler());
	}
	return _inputHandler.get();
}

InputHandler::InputHandler() : mousePos(VEC2(0.0f, 0.0f))
{
	// EMPTY for now
}


InputHandler::~InputHandler() 
{
	// EMPTY for now
}

void InputHandler::Update()
{
	// EMPTY for now
}

void InputHandler::ProcessInput(SDL_Event& _evnt) 
{
	switch (_evnt.type) 
	{
	// mouse motion
	case SDL_MOUSEMOTION:
		mousePos.x = _evnt.motion.x;
		mousePos.y = _evnt.motion.y;
		break;
	
	// mouse buttons
	case SDL_MOUSEBUTTONDOWN:
		if (_evnt.button.button == SDL_BUTTON_LEFT) 
		{
				
		}
		else if (_evnt.button.button == SDL_BUTTON_RIGHT)
		{
			
		}
		break;
	case SDL_MOUSEBUTTONUP:
		
		break;

	// keyboard
	case SDL_KEYDOWN:
		switch (_evnt.key.keysym.sym) {
		case SDLK_w:
			break;
		case SDLK_s:
			break;
		}
	case SDL_KEYUP:
		break;
	}
}

hBOOL InputHandler::IsKeyDown(hINT key) 
{
	return false;
}