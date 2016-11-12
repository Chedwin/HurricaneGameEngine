#include "Texture.h"

Texture::Texture(SdlImage* img, const STRING& name, const STRING& id)
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