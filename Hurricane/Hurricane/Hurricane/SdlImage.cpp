#include "SdlImage.h"
#include "DebugLog.h"


SdlImage::SdlImage(hINT _width, hINT _height) 
	: Image(_width, _height), 
	_surface(nullptr)
{
	Init(_width, _height);
}


SdlImage::SdlImage(STRING& _filePath)
	: Image(_filePath),
	_surface(nullptr)
{
	Init(_filePath);
}

SdlImage::~SdlImage()
{
	if (_surface) {
		SDL_FreeSurface(_surface);	
	}
	_surface = nullptr;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL SdlImage::Init(hINT width, hINT height)
{
	_width = width;
	_height = height;
	return true;
}

hBOOL SdlImage::Init(STRING & filePath)
{
	SDL_Surface* temp = nullptr;
	temp = IMG_Load(filePath.c_str());

	//If the image loaded
	if (!temp)
	{
		PRINTF("IMG_Load() FAILED: %s\n", IMG_GetError());
		//Free the old image
		SDL_FreeSurface(temp);
		return false;
	}

	_surface = temp;

	// set the width and height
	_width = _surface->w;
	_height = _surface->h;

	Uint8 bits = _surface->format->BytesPerPixel;

	if (bits == 4) // does it contain an alpha channel?
	{
		if (_surface->format->Rshift == 24 && _surface->format->Aloss == 0) {
			_colourFormat = GL_ABGR_EXT;
		}
		else if (_surface->format->Rshift == 16 && _surface->format->Aloss == 8) {
			_colourFormat = GL_BGRA;
		}
		else if (_surface->format->Rshift == 16 && _surface->format->Ashift == 24) {
			_colourFormat = GL_BGRA;
		}
		else if (_surface->format->Rshift == 0 && _surface->format->Ashift == 24) {
			_colourFormat = GL_RGBA;
		}
		else {
			LOG->ConsoleError("Pixel Format not recognized for GL display");
			throw std::logic_error("Pixel Format not recognized for GL display");
			return false;
		}
	}
	else if (bits == 3) // no alpha channel
	{
		if (_surface->format->Rshift == 16) {
			_colourFormat = GL_BGR;
		}
		else if (_surface->format->Rshift == 0) {
			_colourFormat = GL_RGB;
		}
		else {
			LOG->ConsoleError("Pixel Format not recognized for GL display");
			throw std::logic_error("Pixel Format not recognized for GL display");
			return false;
		}
	}
	else 
	{
		LOG->ConsoleError("Pixel Format not recognized for GL display");
		throw std::logic_error("Pixel Format not recognized for GL display");
		return false;
	}

	// Set the bits per pixel
	_bitsPerPixel = bits;

	return true;
}



void SdlImage::SetPixel(hINT x, hINT y, hFLOAT r, hFLOAT g, hFLOAT b)
{
	if (x < 0 || x >= GetWidth()) {
		STRING err = "EXCEPTION: X COORDINATE OUT OF RANGE";
		throw std::out_of_range(err.c_str());
	}
	if (y < 0 || y >= GetHeight()) {
		STRING err = "EXCEPTION: Y COORDINATE OUT OF RANGE";
		throw std::out_of_range(err.c_str());
	}

	// Convert the pixels to 32 bit
	Uint32* pixels = (Uint32 *)_surface->pixels;

	//Set the pixel
	hINT rowStart = GetWidth() * 3 * x;
	hINT colStart = y * 3;
	hINT startpos = rowStart + colStart;

	pixels[startpos]	 = (Uint32)r * 255; // red
	pixels[startpos + 1] = (Uint32)g * 255; // green
	pixels[startpos + 2] = (Uint32)b * 255; // blue
}