//*******************************//
//
// Name:			AbstractRenderer.h
// Description:		Abstract class that any rendering system can override.
//					i.e. OpenGL, DirectX
//
// Author:			Edwin Chen
// Created:			Sep 12, 2016
// Last updated:	Oct 09, 2016
//
//*******************************//


#pragma once

#ifndef ABSTRACT_RENDERER_H
#define ABSTRACT_RENDERER_H

#include "Macro.h"
#include "ShaderProgram.h"

class AbstractRenderer {
public:
	AbstractRenderer() {}
	virtual ~AbstractRenderer() {}

	virtual hBOOL Init(STRING winName, hINT width, hINT height, hUINT flags=0) = 0;
	virtual void Render() = 0;
	virtual void SwapBuffers() = 0;
};

#endif