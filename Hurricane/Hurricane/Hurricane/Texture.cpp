#include "Texture.h"

Texture::Texture(SdlImage* img, const STRING& name)
	: imageTexture(img), resourceName(name)
{
	if (imageTexture) {
		width = imageTexture->GetWidth();
		height = imageTexture->GetHeight();
	}
}

Texture::~Texture()
{
	if (imageTexture) {
		delete imageTexture;
	}
	imageTexture = nullptr;
}