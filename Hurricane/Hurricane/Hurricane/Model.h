//*******************************//
//
// Name:			Model.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//


#ifndef MODEL_H
#define MODEL_H


#include <glew.h>
#include "Macro.h"
#include "HMath.h"

class Model {
public:
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

	Model() {}
	virtual ~Model() {}

	virtual void Render() = 0;

protected:
	STRING _name;
};

#endif