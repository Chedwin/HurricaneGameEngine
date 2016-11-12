#include "Debug.h"
#include "Window.h"



Window::Window() : _window(nullptr), _renderer(nullptr)
{
	// EMPTY
}


Window::~Window() {
	Destroy();
}


hBOOL Window::Init(const hINT _w, const hINT _h, const UINT32 flags)
{
	_isInitialized = false;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Debug::Log(EMessageType::FATAL_ERR, "Window", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, std::string(SDL_GetError()));
		return _isInitialized;
	}

	SetWindowSize(_w, _h);

	SDL_CreateWindowAndRenderer(_width, _height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);

	if (_window == nullptr) {
		Debug::ConsoleError("SDL WINDOW CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return _isInitialized;
	}

	if (!_renderer) {
		Debug::ConsoleError("SDL RENDERER CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return _isInitialized;
	}

	//Set up our OpenGL context
	_glContext = SDL_GL_CreateContext(_window);
	if (!_glContext) {
		Debug::ConsoleError("SDL GL CONTEXT CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return false;
	}

	//Set up glew (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::ConsoleError("GLEW CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

	_isInitialized = true;
	return _isInitialized;
}

void Window::Destroy()
{
	SDL_DestroyWindow(_window);
	SDL_GL_DeleteContext(_glContext);
	_window = nullptr;
	_glContext = nullptr;
	_isInitialized = false;
}

void Window::SetWindowSize(const hINT wid, const hINT hgt) {
	_width = wid;
	_height = hgt;
}
