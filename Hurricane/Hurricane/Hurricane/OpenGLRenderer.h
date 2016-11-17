//*******************************//
//
// Name:			OpenGLRenderer.h
// Description:		This creates an OpenGL environment for rendering to the window.
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	Nov 15, 2016
//
//*******************************//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H


#include <glew.h>

#include "Macro.h"
#include "AbstractRenderer.h"

//#include "Window.h"
//#include "ShaderProgramManager.h"
//#include "ImageManager.h"
//#include "HMath.h"

class OpenGLRenderer : public AbstractRenderer {
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	void RenderPrimitive(PrimitiveType prim);
};

#endif