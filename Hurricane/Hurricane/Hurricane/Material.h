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
#include "Colour.h"
#include "Texture.h"


class Material {
public:
	Material(const STRING& _name);
	~Material() {}


	inline void SetMaterialName(const STRING& _name) {
		_matName = _name;
	}
	inline void SetShaderName(const STRING& _name) {
		_shaderName = _name;
	}
	inline STRING GetShaderName() const {
		return _shaderName;
	}
	inline STRING GetMaterialName() const {
		return _shaderName;
	}

protected:
	Colour ambient, diffuse, specular, emissive;
	hFLOAT specCoefficient;

	VECTOR(Texture) texturesList;

	// Name of this material
	STRING _matName;

	// The name of the shader used to render this material
	STRING _shaderName;
	hBOOL _isShaderAttached;
};

#endif