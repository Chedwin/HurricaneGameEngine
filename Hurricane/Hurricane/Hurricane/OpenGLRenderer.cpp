#include "OpenGLRenderer.h"
#include "Game.h"

OpenGLRenderer::OpenGLRenderer() {
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glFrontFace(GL_CCW);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_ONE);*/
	glEnable(GL_DEPTH_TEST);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}


OpenGLRenderer::~OpenGLRenderer()
{
	// EMPTY
}

void OpenGLRenderer::RenderPrimitive(PrimitiveType prim)
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);     // To operate on model-view matrix
	glLoadIdentity();

	/*switch (prim) {
	case PrimitiveType::TRIANGLES:
		break;
	case PrimitiveType::QUADS:
		break;
	case PrimitiveType::NONE:
	default:
		break;
	}*/
}
