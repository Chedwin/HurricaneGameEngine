//*******************************//
//
// Name:			Texture.h
// Description:		Defines a texture that can be applied onto a model.
//
// Author:			Edwin Chen
// Created:			Nov 06, 2016
// Last updated:	Nov 06, 2016
//
//*******************************//

#pragma once


#ifndef CLASS_NAME_H
#define CLASS_NAME_H

#include <glew.h>
#include "Macro.h"
#include "SdlImage.h"

class Texture {
public:
	Texture() {}
	~Texture() {}

	inline STRING GetResourceName() const {
		return resourceName;
	}
	inline hINT GetWidth() const {
		return width;
	}
	inline hINT GetHeight() const {
		return height;
	}
public:
	GLuint textureID;
	STRING	resourceName;
	hINT width, height;

	SdlImage* imageTexture;
};

#endif