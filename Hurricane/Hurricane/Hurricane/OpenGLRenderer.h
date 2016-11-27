//*******************************//
//
// Name:			OpenGLRenderer.h
// Description:		This creates an OpenGL environment for rendering to the window.
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	Nov 26, 2016
//
//*******************************//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H


#include <glew.h>

#include "Macro.h"
#include "AbstractRenderer.h"


class OpenGLRenderer : public AbstractRenderer {
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void RenderPrimitive(PrimitiveType prim);

protected:
	GLuint vao;
};

#endif