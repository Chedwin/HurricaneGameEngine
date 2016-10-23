//*******************************//
//
// Name:			SdlImage.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 22, 2016
// Last updated:	Oct 23, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "Image.h"
#include <SDL_image.h>
#include <glew.h>

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H

class SdlImage : public Image
{
public:
	SdlImage(hINT _width, hINT _height);
	SdlImage(STRING& _filePath);

	~SdlImage();

	inline hINT GetBitsPerPixels() const {
		return surface->format->BitsPerPixel;
	}

	inline hINT GetWidth() const {
		return surface->w;
	}

	inline hINT GetHeight() const {
		return surface->h;
	}

	inline GLenum GetPixelType() {
		return GL_UNSIGNED_BYTE;
	}

	hINT GetPixelStorageParameter() {
		return 4;
	}
	
private:
/* FOR REFERENCE
	THESE ARE THE FILEDS THAT SDL_Surface PROVIDES FOR US FOR SIMPLICITY'S SAKE:

typedef struct SDL_Surface {
	Uint32 flags;                          
	SDL_PixelFormat* format;               
	int w, h;                              
	Uint16 pitch;                          
	void* pixels;                         											
	SDL_Rect clip_rect;                    
	int refcount;                           
} SDL_Surface;
*/
	SDL_Surface* surface;
	//hINT width, height, bitsPerPixel;
	GLenum colourFormat;
protected:
	hBOOL Init(hINT width, hINT height);
	hBOOL Init(STRING& filePath);

public:

	
};

#endif
