//*******************************//
//
// Name:			Texture.h
// Description:		Defines a texture that can be applied onto a model.
//
// Author:			Edwin Chen
// Created:			Nov 06, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew.h>
#include "Macro.h"
#include "SdlImage.h"

class Texture {
public:

	enum TextureDataType {
		Float, UnsignedByte, UnsignedByte_3D
	};

	Texture(SdlImage* img, const STRING& name, const STRING& id);
	~Texture();

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
	TextureDataType dataType;
};

#endif