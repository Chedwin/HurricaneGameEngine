//*******************************//
//
// Name:			Model.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Oct 17, 2016
//
//*******************************//


#ifndef MODEL_H
#define MODEL_H

#pragma once

#include <glew.h>
#include "Macro.h"
#include "Vertex.h"

class Model 
{
public:
	Model() : vertex(nullptr) {}
	virtual ~Model() {}

	virtual void Render() = 0;

	Vertex* vertex;

	void AddVertices();

	void LoadBuffer();

	inline STRING GetName() const {
		return name;
	}

protected:
	STRING name;
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