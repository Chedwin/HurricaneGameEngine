//*******************************//
//
// Name:			Texture.h
// Description:		Defines a texture that can be applied onto a model.
//					Uses a SDL image to load in pixels.
//					Images w/ formats (jpg, png, bmp) can be used.
//
// Author:			Edwin Chen
// Created:			Nov 06, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Macro.h"

class Texture {
protected:
	hBOOL Init(hINT width, hINT height, const STRING& name);
	hBOOL Init(const STRING& filePath, const STRING& name);
public:

	enum TextureDataType {
		Float, UnsignedByte, UnsignedByte_3D
	};

	Texture(hINT _width, hINT _height, const STRING& _name);
	Texture(const STRING& _filePath, const STRING& _name);

	~Texture();
	
	void SetPixel(hINT x, hINT y, hFLOAT r, hFLOAT g, hFLOAT b);

	void* GetPixels() const;

	inline SDL_Surface* GetImageSurface() const {
		return _surface;
	}


	inline GLenum GetPixelType() {
		return GL_UNSIGNED_BYTE;
	}
	inline hINT GetPixelStorageParameter() {
		return 4;
	}

	inline STRING GetResourceName() const {
		return _resourceName;
	}
	inline void SetResourceName(const STRING& name) {
		_resourceName = name;
	}

	inline hINT GetWidth() const {
		return _width;
	}
	inline hINT GetHeight() const {
		return _height;
	}
	inline GLenum GetColourFormat() const {
		return _colourFormat;
	}

protected:
	/* ****** FOR REFERENCE ******
	THESE ARE THE FIELDS THAT SDL_Surface PROVIDES FOR US FOR SIMPLICITY'S SAKE:

	typedef struct SDL_Surface {
		Uint32 flags;
		SDL_PixelFormat* format;
		int w, h;
		Uint16 pitch;
		void* pixels;
		SDL_Rect clip_rect;
		int refcount;
		};
	*/
	SDL_Surface* _surface;
	GLenum _colourFormat;

	STRING	_resourceName;
	hINT _width, _height, _bitsPerPixel;
public:
	TextureDataType dataType;
};

#endif