//*******************************//
//
// Name:			Vertex.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Nov 06, 2016
//
//*******************************//

#pragma once

#ifndef VERTEX_H
#define VERTEX_H

#include <glew.h>
#include "Macro.h"

/*
The VertexComponentDescriptor describes one of the components in a vertex by specifying :
	-the type of the component
	-the size of the component in bytes
	-the offset of the component from the start of the vertex
*/
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

	static STRING ComponentTypeToString(VertexComponentType typ);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
* A VertexDescriptor describes the data layout for a complete vertex.  This describes
* how the individual components are layed out in a vertex and can include the position
* of the vertex, color, etc.
*
* Each component is described by a VertexComponentDescriptor and all of the components
* in the vertex are described by a list of VertexComponentDescriptors.
*/
class VertexDescriptor
{
private:
	VECTOR(VertexComponentDescriptor) componentList;
	hINT componentIndex[12];
	hINT stride;

public:
	VertexDescriptor();
	~VertexDescriptor() {}

	VertexComponentDescriptor GetComponent(hINT index) const;

	inline hINT GetStride() const {
		return stride;
	}
	inline hINT GetSize() const {
		return componentList.size();
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