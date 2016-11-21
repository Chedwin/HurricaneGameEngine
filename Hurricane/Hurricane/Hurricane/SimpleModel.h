//*******************************//
//
// Name:			SimpleModel.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 20, 2016
//
//*******************************//


#ifndef SIMPLE_MODEL_H
#define SIMPLE_MODEL_H

#include <glew.h>
#include "Macro.h"
#include "Model.h"

// Simple model represents a mesh
class SimpleModel : public Model
{
public:
	SimpleModel();
	~SimpleModel();

	void Render();
};


#endif