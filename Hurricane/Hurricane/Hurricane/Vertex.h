//*******************************//
//
// Name:			Vertex.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Oct 08, 2016
//
//*******************************//

#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include "Macro.h"

struct Vertex 
{
	struct Position 
	{
		hFLOAT x, y, z;
	};

	struct Colour 
	{
		GLubyte red, blue, green, alpha;
	};

	Position pos;
	Colour col;
};

#endif