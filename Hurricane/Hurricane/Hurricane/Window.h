//*******************************//
//
// Name:			Window.h
// Description:		Creates and handles the window.
//					SDL is used to create an initial window
//					An OpenGL context will then draw to said SDL window
//
// Author:			Edwin Chen
// Created:			Feb 04, 2016
// Last updated:	Dec 09, 2016
//
//*******************************//

#ifndef _WINDOW_H
#define _WINDOW_H

////// Since SDL is a 3rd party SDK, it should NOT be macro-defined in our project
#include <SDL.h>
#include <glew.h>

#include "Macro.h"


class Window {
public:
	Window();
	~Window();

	/// C11 precautions delete these non-needed default constructors and operators
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator = (const Window&) = delete;
	Window& operator = (Window&&) = delete;

	hBOOL Init(const hINT _w, const hINT _h);

	void Destroy();

	void SetWindowSize(const hINT wid, const hINT hgt);
	void SetFullScreen(hBOOL b);

	inline hINT GetWidth() const {
		return _width;
	}
	inline hINT GetHeight() const {
		return _height;
	}

	inline SDL_Window* GetWindow() const {
		return _window;
	}
	inline SDL_Renderer* GetRenderer() const {
		return _renderer;
	}

	inline hBOOL IsFullScreen() const {
		return _isFullScreen;
	}

private:
	hBOOL _isInitialized;
	hBOOL _isFullScreen;

private:
	SDL_GLContext _glContext;

	hINT _width, _height;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
};


#endif