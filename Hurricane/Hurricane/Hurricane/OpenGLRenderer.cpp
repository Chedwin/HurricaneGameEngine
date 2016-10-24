#include "OpenGLRenderer.h"
#include "DebugLog.h"
#include "Vertex.h"
#include <SDL_image.h>
#include "SdlImage.h"


OpenGLRenderer::OpenGLRenderer() : _gameWindow(nullptr), _gameRenderer(nullptr)
{
	// EMPTY
}


OpenGLRenderer::~OpenGLRenderer()
{
	SDL_DestroyRenderer(_gameRenderer); _gameRenderer = nullptr;
	SDL_DestroyWindow(_gameWindow);		_gameWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

hBOOL OpenGLRenderer::Init(STRING winName, hINT width, hINT height, hUINT flags)
{
	_winWidth = width;
	_winHeight = height;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_RendererInfo displayRendererInfo;

	//Open an SDL window
	_gameWindow = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (_gameWindow == nullptr) {
		LOG->Error("SDL WINDOW CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	_gameRenderer = SDL_CreateRenderer(_gameWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!_gameRenderer) {
		LOG->Error("SDL RENDERER CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	SDL_GetRendererInfo(_gameRenderer, &displayRendererInfo);

	//Set up our OpenGL context
	SDL_GLContext glContext = SDL_GL_CreateContext(_gameWindow);
	if (glContext == nullptr) {
		LOG->Error("SDL GL CONTEXT CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	//Set up glew (optional but recommended)
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		LOG->Error("GLEW CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}




	// Init PNG & JPG image usage
	hINT imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	hINT status = IMG_Init(imgFlags);

	if (!(status & imgFlags)) {
		LOG->Error("SDL IMAGE PNG CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	//Check the OpenGL version
	PRINTF("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

	////////////
	// TODO: INITIALIZE OTHER OPENGL STUFF HERE
	////////////
	GLsizei _width, _height;
	_width = width;
	_height = height;


	// Change the NDC viewport screen ratio accordingly based on window width & height
	glViewport(0, 0, _width, _height);

	glEnable(GL_CULL_FACE | GL_DEPTH_TEST | GL_BLEND);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glFrontFace(GL_CCW);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_SetSwapInterval(1);

	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	return true;
}


void OpenGLRenderer::Render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);     // To operate on model-view matrix
	glLoadIdentity();
}

void OpenGLRenderer::SwapBuffers()
{
	// Double buffering 
	SDL_GL_SwapWindow(_gameWindow); 
}
