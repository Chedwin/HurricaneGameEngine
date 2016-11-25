#include "InputHandler.h"
#include "Debug.h"
#include "Game.h"

UNIQUE_PTR(InputHandler) InputHandler::_inputHandler(nullptr);

InputHandler* InputHandler::GetInputHandler() 
{
	if (_inputHandler.get() == nullptr) 
	{
		/// I originally set the uniqu_evntptr to be null in the constructor - reset() sets the new address
		_inputHandler.reset(new InputHandler());
	}
	return _inputHandler.get();
}

// Initialize mouse and keyboard maps
InputHandler::InputHandler()
{
	// MOUSE BUTTONS
	_curMouseMap.insert(PAIR(Uint8, hBOOL)(SDL_BUTTON_LEFT, false));
	_curMouseMap.insert(PAIR(Uint8, hBOOL)(SDL_BUTTON_MIDDLE, false));
	_curMouseMap.insert(PAIR(Uint8, hBOOL)(SDL_BUTTON_RIGHT, false));
	_oldMouseMap = _curMouseMap; //Everything should be false so this just makes sure nothing goes wrong in frame 1

	// MOUSE POSITION
	_curMousePos = VEC2(0.0f, 0.0f);
	_oldMousePos = VEC2(0.0f, 0.0f);
	motionEvent = SDL_MouseMotionEvent();

	// KEYBOARD BUTTONS

	// 0-9 alphanumeric keys
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_0, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_1, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_2, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_3, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_4, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_5, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_6, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_7, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_8, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_9, false));

	// alphabet
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_a, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_b, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_c, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_d, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_e, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_f, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_g, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_h, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_i, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_j, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_k, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_l, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_m, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_n, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_o, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_p, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_q, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_r, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_s, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_t, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_u, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_v, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_w, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_x, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_y, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_z, false));


	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_BACKSPACE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_CANCEL, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_CAPSLOCK, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_COMMA, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_DELETE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_DOWN, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_END, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_EQUALS, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_ESCAPE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_BACKQUOTE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_HOME, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_INSERT, false));

	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_0, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_1, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_2, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_3, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_4, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_5, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_6, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_7, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_8, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_9, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_DECIMAL, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_DIVIDE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_ENTER, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_PLUS, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_MINUS, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_KP_MULTIPLY, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LALT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LCTRL, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LEFT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LEFTBRACKET, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LSHIFT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_MINUS, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_NUMLOCKCLEAR, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_PAGEDOWN, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_PAGEUP, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_PERIOD, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_PRINTSCREEN, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RALT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RCTRL, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RIGHT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LSHIFT, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RIGHTBRACKET, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_SCROLLLOCK, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_SEMICOLON, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_SLASH, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_SPACE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_TAB, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_UP, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_PAUSE, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_MENU, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_BACKSLASH, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RETURN, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_LGUI, false));
	_curKeyboardMap.insert(PAIR(SDL_Keycode, hBOOL)(SDLK_RGUI, false));
	_oldKeyboardMap = _curKeyboardMap; 
}


InputHandler::~InputHandler() 
{
	// EMPTY for now
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// BASIC LOGIC

void InputHandler::Update()
{
	_oldMousePos = _curMousePos;
	_oldKeyboardMap = _curKeyboardMap;
	_oldMouseMap = _curMouseMap;

	hINT x, y;
	SDL_GetMouseState(&x, &y);
	SetMouseCoord(x, y);

	motionEvent = SDL_MouseMotionEvent();
}

void InputHandler::ProcessInput(SDL_Event& _evnt) 
{
	switch (_evnt.type) {
	case SDL_KEYDOWN:
		PressKey(_evnt.key.keysym.sym);
		break;
	case SDL_KEYUP:
		ReleaseKey(_evnt.key.keysym.sym);
		break;
	case SDL_MOUSEBUTTONDOWN:
		HitMouse(_evnt.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		ReleaseMouse(_evnt.button.button);
		break;
	case SDL_MOUSEMOTION:
		motionEvent = _evnt.motion;
		break;
	}
	
}



///////////////////////////////////////////////////////////////////////////////////////////////////////

// KEYBOARD HANDLING

void InputHandler::PressKey(SDL_Keycode keyid)
{
	_curKeyboardMap[keyid] = true;
}

void InputHandler::ReleaseKey(SDL_Keycode keyid)
{
	_curKeyboardMap[keyid] = false;
}

hBOOL InputHandler::IsAnyKeyDown()
{
	for (auto it = _curKeyboardMap.begin(); it != _curKeyboardMap.end(); it++)
	{
		if (it->second == true)
			return true;
	}

	for (auto it = _curMouseMap.begin(); it != _curMouseMap.end(); it++)
	{
		if (it->second == true)
			return true;
	}

	return false;
}

hBOOL InputHandler::IsKeyDown(SDL_Keycode key_) {
	return (_curKeyboardMap[key_]);
}

hBOOL InputHandler::IsKeyPressed(SDL_Keycode key_) {
	return (!_oldKeyboardMap[key_] && _curKeyboardMap[key_]);
}

hBOOL InputHandler::IsKeyReleased(SDL_Keycode key_) {
	return (_oldKeyboardMap[key_] && !_curKeyboardMap[key_]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

// MOUSE BUTTONS

void InputHandler::HitMouse(Uint8 key_) {
	_curMouseMap[key_] = true;
}

void InputHandler::ReleaseMouse(Uint8 key_) {
	_curMouseMap[key_] = false;
}

void InputHandler::SetMouseCoord(const hFLOAT x, const hFLOAT y)
{
	_curMousePos = VEC2(x, y);
}

bool InputHandler::IsMouseButtonDown(Uint8 button_) {
	return _curMouseMap[button_];
}

bool InputHandler::IsMouseButtonPressed(Uint8 button_) {
	return (!_oldMouseMap[button_] && _curMouseMap[button_]);
}

bool InputHandler::IsMouseButtonReleased(Uint8 button_) {
	return (_oldMouseMap[button_] && !_curMouseMap[button_]);
}