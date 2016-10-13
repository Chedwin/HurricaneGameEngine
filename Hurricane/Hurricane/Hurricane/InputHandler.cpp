#include "InputHandler.h"
#include "DebugLog.h"
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

InputHandler::InputHandler() : mousePos(VECTOR2(0.0f, 0.0f))
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
		//COUT << "x: " << mousePos.x << " ";
		//COUT << "y: " << mousePos.y << ENDL;
		break;
	
	// mouse buttons
	case SDL_MOUSEBUTTONDOWN:
		if (_evnt.button.button == SDL_BUTTON_LEFT) 
		{
			LOG->ConsoleLog("Mouse left");		
		}
		else if (_evnt.button.button == SDL_BUTTON_RIGHT)
		{
			LOG->ConsoleLog("Mouse right");
		}
		break;
	case SDL_MOUSEBUTTONUP:
		LOG->ConsoleLog("Mouse up");
		break;

	// keyboard
	case SDL_KEYDOWN:
		switch (_evnt.key.keysym.sym) {
		case SDLK_w:
			GAME->cam3D->SetPosition(GAME->cam3D->GetCameraPos() + VECTOR3(0.0f, 1.0f, 0.0f));
			break;
		case SDLK_s:
			GAME->cam3D->SetPosition(GAME->cam3D->GetCameraPos() + VECTOR3(0.0f, -1.0f, 0.0f));
			break;
		}
	case SDL_KEYUP:
		COUT << "UpKey" << ENDL;
		break;
	}
}