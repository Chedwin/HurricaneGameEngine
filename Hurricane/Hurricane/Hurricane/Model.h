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
	Model() {}
	virtual ~Model() {}

	virtual void Render() {}

	inline STRING GetModelName() {
		return _name;
	}
	inline void SetModelName(const STRING& n) {
		_name = n;
	}

protected:
	STRING _name;
public:
	VECTOR(VEC3) vertex;
	VECTOR(VEC2) uvs;
	VECTOR(VEC3) normals;
};

#endif