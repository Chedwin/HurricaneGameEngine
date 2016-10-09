#include "OpenGLRenderer.h"
#include "DebugLog.h"
#include "Vertex.h"
OpenGLRenderer::OpenGLRenderer() : _gameWindow(nullptr), _gameRenderer(nullptr)
{
}
GLuint Buffers[2];

OpenGLRenderer::~OpenGLRenderer()
{
	glDeleteBuffers(1, Buffers);
	SDL_DestroyRenderer(_gameRenderer); _gameRenderer = nullptr;
	SDL_DestroyWindow(_gameWindow);		_gameWindow = nullptr;
	SDL_Quit();
}


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


	// CREATE THE SHADERS
	CreateShaders();

	Vertex v[4];
	v[0].pos = { -0.5f, -0.5f, 0.0f };
	v[1].pos = { -0.5f, 0.5f, 0.0f };
	v[2].pos = { 0.5f, 0.5f, 0.0f };
	v[3].pos = { 0.5f, -0.5f, 0.0f };

	for (int i = 0; i < 4; i++) {
		v[i].col = { 0, 0, 255, 1 };
	}
	

	glGenBuffers(2, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	glEnableVertexAttribArray(1);


	_shaderLocation = shaderProgram.GetUniformLocation("model_matrix");

	return true;
}

void OpenGLRenderer::CreateShaders() 
{
	shaderProgram.CompileShaders("colourShading.vert", "colourShading.frag");
	shaderProgram.AddAttribute("vertexPosition");
	shaderProgram.AddAttribute("vertexColor");
	shaderProgram.LinkShaders();
}

void OpenGLRenderer::Render()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

	shaderProgram.UseShader();

	glm::mat4 model_view;
	glUniformMatrix4fv(_shaderLocation, 1, GL_FALSE, &model_view[0][0]);
	glDrawArrays(GL_QUADS, 0, 4);

	shaderProgram.UnuseShader();
}

void OpenGLRenderer::SwapBuffers()
{
	// Double buffering 
	SDL_GL_SwapWindow(_gameWindow); 
}
