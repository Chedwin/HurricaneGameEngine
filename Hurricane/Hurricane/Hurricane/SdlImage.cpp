#include "SdlImage.h"
#include "DebugLog.h"


SdlImage::SdlImage(hINT _width, hINT _height) 
	: Image(_width, _height), 
	surface(nullptr)
{
	Init(_width, _height);
}


SdlImage::SdlImage(STRING& _filePath)
	: Image(_filePath),
	surface(nullptr)
{
	Init(_filePath);
}

SdlImage::~SdlImage()
{
	if (surface) {
		SDL_FreeSurface(surface);	
	}
	surface = nullptr;
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL SdlImage::Init(hINT width, hINT height)
{
	surface->w = width;
	surface->h = height;
	return true;
}

hBOOL SdlImage::Init(STRING & filePath)
{
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(filePath.c_str());

	//If the image loaded
	if (!temp)
	{
		PRINTF("IMG_Load FAILED: %s\n", IMG_GetError());
		//Free the old image
		SDL_FreeSurface(temp);
		return false;
	}

	surface = temp;


	Uint8 bits = surface->format->BytesPerPixel;

	if (bits == 4) // contains an alpha channel
	{
		if (surface->format->Rshift == 24 && surface->format->Aloss == 0) {
			colourFormat = GL_ABGR_EXT;
		}
		else if (surface->format->Rshift == 16 && surface->format->Aloss == 8) {
			colourFormat = GL_BGRA;
		}
		else if (surface->format->Rshift == 16 && surface->format->Ashift == 24) {
			colourFormat = GL_BGRA;
		}
		else if (surface->format->Rshift == 0 && surface->format->Ashift == 24) {
			colourFormat = GL_RGBA;
		}
		else {
			LOG->ConsoleError("Pixel Format not recognized for GL display");
			throw std::logic_error("Pixel Format not recognized for GL display");
			return false;
		}
	}
	else if (bits == 3) // no alpha channel
	{
		if (surface->format->Rshift == 16) {
			colourFormat = GL_BGR;
		}
		else if (surface->format->Rshift == 0) {
			colourFormat = GL_RGB;
		}
		else {
			LOG->ConsoleError("Pixel Format not recognized for GL display");
			throw std::logic_error("Pixel Format not recognized for GL display");
		}
	}
	else 
	{
		LOG->ConsoleError("Pixel Format not recognized for GL display");
		throw std::logic_error("Pixel Format not recognized for GL display");
	}

	return true;
}