//*******************************//
//
// Name:			AbstractRenderer.h
// Description:		Abstract class that any rendering system can override.
//					i.e. OpenGL, DirectX
//
// Author:			Edwin Chen
// Created:			Sep 12, 2016
// Last updated:	Nov 04, 2016
//
//*******************************//


#pragma once

#ifndef ABSTRACT_RENDERER_H
#define ABSTRACT_RENDERER_H

#include "Macro.h"
#include "Window.h"

enum PrimitiveType {
	NONE,
	QUADS,
	TRIANGLES
};

class AbstractRenderer {
public:
	AbstractRenderer() {}
	virtual ~AbstractRenderer() {}

	virtual void RenderPrimitive(PrimitiveType prim) = 0;

protected:
	Window* winRef; // reference the game window
};

#endif