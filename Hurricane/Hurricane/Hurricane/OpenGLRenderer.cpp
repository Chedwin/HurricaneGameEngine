#include "OpenGLRenderer.h"
#include "Game.h"



OpenGLRenderer::OpenGLRenderer() {
	/*glEnable(GL_CULL_FACE | GL_DEPTH_TEST | GL_BLEND);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glFrontFace(GL_CCW);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	winRef = GAME->gameWindow;*/

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
}


OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::RenderPrimitive(PrimitiveType prim)
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);     // To operate on model-view matrix
	glLoadIdentity();

	switch (prim) {
	case PrimitiveType::TRIANGLES:
		break;
	case PrimitiveType::QUADS:
		break;
	case PrimitiveType::NONE:
	default:
		break;
	}
}
