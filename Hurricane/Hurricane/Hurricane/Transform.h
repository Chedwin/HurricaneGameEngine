//*******************************//
//
// Name:			Transform.h
// Description:		Basic transform struture to define position, scale, and rotation.
//					Very similar to Unity transform design.
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "HMath.h"

struct Transform {
	VEC3 position;
	VEC3 scale;
	QUATERNION rotation;

	inline void Translate(const VEC3& p) {
		position = p;
	}
	inline void Scale(const VEC3& s) {
		scale = s;
	}
	inline void Rotate(const QUATERNION& q) {
		rotation = q;
	}
};


#endif