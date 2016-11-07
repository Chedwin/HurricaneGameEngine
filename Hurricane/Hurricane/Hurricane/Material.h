//*******************************//
//
// Name:			Material.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 31, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef MATERIAL_H
#define MATERIAL_H

#include "Macro.h"
#include "HMath.h"
#include "Color.h"
#include "Texture.h"


class Material {
public:
	Material();
	~Material() {}

	inline void SetMaterialName(const STRING& _name) {
		matName = _name;
	}

	inline STRING GetShaderName() const {
		return shaderName;
	}

public:
	Color ambient, diffuse, specular, emissive;
	hFLOAT specCoefficient;

	VECTOR(Texture) texturesList;

	// Name of this material
	STRING matName;

	// The name of the shader used to render this material
	STRING shaderName;
	hBOOL isShaderAttached;
};

#endif