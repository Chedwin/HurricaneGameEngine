#include "TextureManager.h"
#include "Debug.h"

UNIQUE_PTR(TextureManager) TextureManager::_textureManager(nullptr); // Declare static unique pointer

TextureManager* TextureManager::GetTextureManager() {
	if (_textureManager.get() == nullptr) {
		_textureManager.reset(new TextureManager());
	}
	return _textureManager.get();
}


TextureManager::TextureManager()
{
	// EMPTY
}

TextureManager::~TextureManager()
{
	ClearAllTextures(); // clean up 
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ResourceHandle<Texture> TextureManager::UploadTexture(const STRING & _name, Texture * _Texture)
{
	ResourceHandle<Texture> result(-1);

	// Check if the resource name is already in use
	result = _textureResources.Get(_name);
	if (!result.IsNull()) {
		Debug::ConsoleError("Texture named '" + _name + "' is already in use");

		return result;
	}

	result = _textureResources.Add(_name, _Texture);
	return result;
}

ResourceHandle<Texture> TextureManager::UploadTextureFromFile(const STRING& _filePath, const STRING& _name)
{
	ResourceHandle<Texture> result(-1);

	// Check if the resource name is already in use
	result = _textureResources.Get(_name);
	if (!result.IsNull()) {
		Debug::ConsoleError("Texture named '" + _name + "' is already in use");
		return result;
	}

	Texture* texture = new Texture(_filePath, _name);
	texture->SetResourceName(_name);
	result = _textureResources.Add(_name, texture);
	return result;
}

void TextureManager::DeleteTexture(const STRING & _name)
{
	_textureResources.Remove(_name);
}

void TextureManager::ClearAllTextures()
{
	_textureResources.EmptyResourceMap();
}

ResourceHandle<Texture> TextureManager::GetTextureHandle(const STRING & _name)
{
	return _textureResources.Get(_name);
}

Texture* TextureManager::GetTexture(ResourceHandle<Texture>& _handle)
{
	return _textureResources.Get(_handle);
}

Texture* TextureManager::GetTexture(const STRING & _name)
{
	Texture* result = nullptr;
	ResourceHandle<Texture> handle = GetTextureHandle(_name);

	if (handle.IsNull()) {
		Debug::ConsoleError("Texture named '" + _name + "' does not exist in TextureManager");
		return result;
	}
	result = TextureManager::GetTexture(handle);
	return result;
}
