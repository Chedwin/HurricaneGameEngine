//*******************************//
//
// Name:			SdlImage.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 22, 2016
// Last updated:	Nov 01, 2016
//
//*******************************//

#pragma once

#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Macro.h"
#include "Image.h"

#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H

class SdlImage : public Image
{
public:
	SdlImage(hINT _width, hINT _height, const STRING& _name = "");
	SdlImage(const STRING& _filePath, const STRING& _name = "");

	~SdlImage();

	void SetPixel(hINT x, hINT y, hFLOAT r, hFLOAT g, hFLOAT b);

	inline SDL_Surface* GetImageSurface() const {
		return _surface;
	}



	inline GLenum GetPixelType() {
		return GL_UNSIGNED_BYTE;
	}

	hINT GetPixelStorageParameter() {
		return 4;
	}
	
private:
/* FOR REFERENCE
	THESE ARE THE FIELDS THAT SDL_Surface PROVIDES FOR US FOR SIMPLICITY'S SAKE:

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
	GLenum _colourFormat;
	
protected:
	hBOOL Init(hINT width, hINT height);
	hBOOL Init(const STRING& filePath);
	
};

#endif
