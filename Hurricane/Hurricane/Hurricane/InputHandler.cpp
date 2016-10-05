#include "InputHandler.h"

UNIQUE_PTR(InputHandler) InputHandler::_inputHandler(nullptr);

InputHandler* InputHandler::GetInputHandler() {
	if (_inputHandler.get() == nullptr) {
		/// I originally set the unique_ptr to be null in the constructor - reset() sets the new address
		_inputHandler.reset(new InputHandler());
	}
	return _inputHandler.get();
}

InputHandler::InputHandler() {
}


InputHandler::~InputHandler() {
}

void InputHandler::Update()
{
}

void InputHandler::TakeEvent(SDL_Event& _evnt) 
{
	switch (_evnt.type) {
		case SDL_KEYDOWN:
			COUT << "DownKey" << ENDL;
			break;
		case SDL_KEYUP:
			COUT << "UpKey" << ENDL;
			break;
	}
}