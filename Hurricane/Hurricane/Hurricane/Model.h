//*******************************//
//
// Name:			Model.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//


#ifndef MODEL_H
#define MODEL_H


#include <glew.h>
#include "Macro.h"
#include "Vertex.h"

class Model {
public:
	Model() {}
	virtual ~Model() {}

	virtual void Render() = 0;

	void LoadBuffer();

	inline STRING GetName() const {
		return _name;
	}

protected:
	STRING _name;
public:
	//Lists of all vertecies, edges, faces and normals
	VECTOR(VEC3) vertex;
	VECTOR(hUINT) edge;
	VECTOR(hUINT) face;
	VECTOR(VEC3) normal;
	VECTOR(VEC3) faceNormal;
	VECTOR(VEC2) textureMap;

	hUINT offsetVertex;
};

// Simple model represents a mesh
class SimpleModel : public Model 
{
public:
	SimpleModel();
	~SimpleModel();

	void Render();



};



#endif