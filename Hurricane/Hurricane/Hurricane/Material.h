//*******************************//
//
// Name:			Material.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 31, 2016
// Last updated:	Nov 06, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "HMath.h"

#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	Material(hFLOAT _ambient, hFLOAT _diffuse, hFLOAT _specular) 
	{
		ambient = _ambient;
		diffuse = _diffuse;
		specular = _specular;
	}

	~Material() {}

	inline VEC3 GetMaterial() {
		return VEC3(ambient, diffuse, specular);
	}

public:
	hFLOAT ambient, diffuse, specular;
};

#endif