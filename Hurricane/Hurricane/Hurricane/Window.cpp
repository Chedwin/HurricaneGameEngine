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

	// (1) Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Debug::Log(EMessageType::FATAL_ERR, "Window", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, std::string(SDL_GetError()));
		return _isInitialized;
	}

	// (2) Set Attributes for OpenGL
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // enable double buffering

	// (3) Set the window size
	SetWindowSize(_w, _h);


	// (4) Create the window and renderer 
	SDL_CreateWindowAndRenderer(_width, _height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);

	if (_window == nullptr) {
		Debug::ConsoleError("SDL WINDOW CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return _isInitialized;
	}

	if (!_renderer) {
		Debug::ConsoleError("SDL RENDERER CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return _isInitialized;
	}

	// (5) Set up our OpenGL context and pass it to the window
	_glContext = SDL_GL_CreateContext(_window);
	if (!_glContext) {
		Debug::ConsoleError("SDL GL CONTEXT CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return false;
	}

	// (6) Init GLEW (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::ConsoleError("GLEW CANNOT BE INITIALIZED", __FILE__, __LINE__);
		return false;
	}


	// (7) Use this function to set the swap interval for the current OpenGL context. 0 - immediate swapping
	// Turn on VSYNC
	SDL_GL_SetSwapInterval(1);

	// (8) Display the current version of OpenGL in the console
#if defined(DEBUG) || defined(_DEBUG)
	PRINTF("***     OpenGL Version: %s   ***", glGetString(GL_VERSION));
#endif

	// (9) Set the initialized to true and return it
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
