//*******************************//
//
// Name:			Vertex.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Oct 30, 2016
//
//*******************************//

#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <glew.h>
#include "Macro.h"

class VertexComponentDescriptor {
public:
	enum VertexComponentType 
	{
		VERTEX_COMP_TYPE_NULL = 0,
		VERTEX_COMP_TYPE_IGNORE_2F,
		VERTEX_COMP_TYPE_IGNORE_3F,
		VERTEX_COMP_TYPE_IGNORE_4F,
		VERTEX_COMP_TYPE_VERTEX_3F,
		VERTEX_COMP_TYPE_NORMAL_3F,
		VERTEX_COMP_TYPE_COLOR_3F,
		VERTEX_COMP_TYPE_COLOR_4F,
		VERTEX_COMP_TYPE_TEX1_2F,
		VERTEX_COMP_TYPE_TEX2_2F,
		VERTEX_COMP_TYPE_TEX3_2F,
		VERTEX_COMP_TYPE_TEX4_2F,
		VERTEX_COMP_TYPE_TEX5_2F,
		VERTEX_COMP_TYPE_TEX6_2F,
		VERTEX_COMP_TYPE_TEX7_2F,
		VERTEX_COMP_TYPE_TEX8_2F
	};

	VertexComponentType type;
	hINT offset;

	VertexComponentDescriptor() : type(VERTEX_COMP_TYPE_NULL), offset(0) {}

	hINT GetNumFloats();
	hINT GetSize();
};

class VertexDescriptor
{
private:
	VECTOR(VertexComponentDescriptor) componentList;
	hINT componentIndex[12];
	hINT stride;

public:
	VertexDescriptor();

	inline hINT GetStride() const {
		return stride;
	}
};

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