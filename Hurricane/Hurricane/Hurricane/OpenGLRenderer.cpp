#include "OpenGLRenderer.h"
#include "Game.h"

OpenGLRenderer::OpenGLRenderer() {
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}


OpenGLRenderer::~OpenGLRenderer()
{
	// EMPTY
}

// NOTE: this function acts as a PRE-RENDER for the game
// thus, setting up the OpenGL environment to accept vertices to be drawn
void OpenGLRenderer::RenderPrimitive(PrimitiveType prim)
{
	// Accept fragment if it closer to the camera than the former one
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// To operate on model-view matrix
	glMatrixMode(GL_MODELVIEW);     
}