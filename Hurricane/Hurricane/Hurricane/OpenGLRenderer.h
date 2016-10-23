//*******************************//
//
// Name:			OpenGLRenderer.h
// Description:		This renderer uses a SDL window w/ a GL Context to draw to the screen
//
// Author:			Edwin Chen
// Created:			Sep 20, 2016
// Last updated:	Oct 08, 2016
//
//*******************************//

#pragma once

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <glew.h>
#include "Macro.h"
#include "Game.h"
#include "AbstractRenderer.h"
#include "ShaderProgramManager.h"
#include "ImageManager.h"
#include "HMath.h"

class OpenGLRenderer : public AbstractRenderer 
{
public:
	OpenGLRenderer();
	~OpenGLRenderer();

	hBOOL Init(STRING winName, hINT width, hINT height, hUINT flags);
	void CreateShaders();

	void Render();
	void SwapBuffers();

	inline SDL_Window* GetWindow() const {
		return _gameWindow;
	}

private:

	SDL_Window* _gameWindow;
	SDL_Renderer* _gameRenderer;

	ShaderProgramManager* _shaderManager;

	GLuint _viewMatLocation;
	GLuint _projMatLocation;
	GLuint _shaderLocation;
	ShaderProgram* _shaderProgram;
	ImageManager* _imageManager;
	GLuint Buffers[2];

};

#endif