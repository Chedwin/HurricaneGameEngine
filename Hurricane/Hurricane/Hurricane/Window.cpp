#include "Debug.h"
#include "Window.h"
#include "HurricaneProperties.h"


Window::Window() : _window(nullptr), _renderer(nullptr)
{
	// EMPTY
}


Window::~Window() {
	Destroy();
}


hBOOL Window::Init(const hINT _w, const hINT _h)
{
	_isInitialized = false;

	// (1) Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Debug::Log(EMessageType::FATAL_ERR, "Window", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, STRING(SDL_GetError()));
		return _isInitialized;
	}

	// (2) Set Attributes for OpenGL
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // enable double buffering

	// (3) Set the window size
	SetWindowSize(_w, _h);


	// (4) Create the window and renderer 
	SDL_CreateWindowAndRenderer(_width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN, &_window, &_renderer);

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

	// (8) Get Moniter Refresh Rate
	SDL_DisplayMode target, moniter;
	target.w = H_PROPERTIES->GetVideoProperties()->screenWidth;
	target.h = H_PROPERTIES->GetVideoProperties()->screenHeight;
	target.format = 0;  // don't care
	target.refresh_rate = 0; // don't care
	target.driverdata = 0; // initialize to 0
	SDL_GetClosestDisplayMode(0, &target, &moniter);


	// (9) Display the current version of OpenGL in the console
#if defined(DEBUG) || defined(_DEBUG)
	PRINTF("***     OpenGL Version: %s   ***\n", glGetString(GL_VERSION));
#endif

	// (10) Set the initialized to true and return it
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

void Window::SetFullScreen(hBOOL b)
{
	if (b) 
	{
		SDL_SetWindowFullscreen(_window, SDL_WINDOW_FULLSCREEN);
		_isFullScreen = true;
	}
	else 
	{
		SDL_SetWindowFullscreen(_window, 0);
		_isFullScreen = false;
	}
}
