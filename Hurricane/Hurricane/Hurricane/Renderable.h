//*******************************//
//
// Name:			Renderable.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 29, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//


#include "Macro.h"
#include "HMath.h"

#ifndef RENDERABLE_H
#define RENDERABLE_H

struct Renderable
{
	struct Mesh
	{
		VECTOR(VEC3) vertex;
		VECTOR(hUINT) edge;
		VECTOR(hUINT) face;
		VECTOR(VEC3) normal;
		VECTOR(VEC3) faceNormal;
		VECTOR(VEC2) textureMap;

		hUINT offsetVertex;
	};

	Renderable() {}
	~Renderable() {}
};

#endif