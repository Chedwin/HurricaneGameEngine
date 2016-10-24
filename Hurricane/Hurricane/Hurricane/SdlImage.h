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
	SdlImage(const STRING& _filePath);

	~SdlImage();

	void SetPixel(hINT x, hINT y, hFLOAT r, hFLOAT g, hFLOAT b);

	inline SDL_Surface* GetImageSurface() const {
		return _surface;
	}

	inline hINT GetBitsPerPixels() const {
		return _bitsPerPixel;
	}

	inline hINT GetWidth() const {
		return _width;
	}

	inline hINT GetHeight() const {
		return _height;
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
	SDL_Surface* _surface;
	hINT _width, _height, _bitsPerPixel;
	GLenum _colourFormat;
	//hCHAR* _imageBytes;
protected:
	hBOOL Init(hINT width, hINT height);
	hBOOL Init(const STRING& filePath);

public:

	
};

#endif
