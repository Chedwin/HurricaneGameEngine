#include "OpenGLRenderer.h"
#include "DebugLog.h"

OpenGLRenderer::OpenGLRenderer() : _gameWindow(nullptr), _gameRenderer(nullptr)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	SDL_DestroyRenderer(_gameRenderer); _gameRenderer = nullptr;
	SDL_DestroyWindow(_gameWindow);		_gameWindow = nullptr;
	SDL_Quit();
}

GLuint Buffers[2];

hBOOL OpenGLRenderer::Init(STRING winName, hINT width, hINT height, hUINT flags)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Open an SDL window
	_gameWindow = SDL_CreateWindow(winName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_OPENGL);

	if (_gameWindow == nullptr) {
		LOG->Error("SDL WINDOW CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

	_gameRenderer = SDL_CreateRenderer(_gameWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!_gameRenderer) {
		LOG->Error("SDL RENDERER CANNOT BE INITIALIZED", __LINE__, __FILE__);
		return false;
	}

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

	//Check the OpenGL version
	PRINTF("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));
	////////////
	// TODO: INITIALIZE OPENGL STUFF HERE
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

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	shaderProgram.CompileShaders("colourShading.vert", "colourShading.frag");
	shaderProgram.LinkShaders();

	GLfloat vertices[4][3] = {
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f, 0.5f, 0.0f },
		{ 0.5f, 0.5f, 0.0f },
		{ 0.5f, -0.5f, 0.0f }
	};

	GLfloat colorData[4][3] = {
		{ 1, 0, 0 },
		{ 1, 1, 0 },
		{ 0, 1, 0 },
		{ 1, 1, 1 }
	};


	glGenBuffers(2, Buffers);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindAttribLocation(shaderProgram.GetProgramID(), 0, "vertexPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glBindAttribLocation(shaderProgram.GetProgramID(), 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	return true;
}

void OpenGLRenderer::Render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.UseShader();

	glDrawArrays(GL_QUADS, 0, 4);
	shaderProgram.UnuseShader();
}

void OpenGLRenderer::SwapBuffers()
{
	// Double buffering 
	SDL_GL_SwapWindow(_gameWindow); 
}
