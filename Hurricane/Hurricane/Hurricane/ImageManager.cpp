#include "ImageManager.h"
#include "SdlImage.h"

UNIQUE_PTR(ImageManager) ImageManager::_imgManager(nullptr); // Declare static unique pointer

ImageManager* ImageManager::GetImageManager() {
	if (_imgManager.get() == nullptr) {
		_imgManager.reset(new ImageManager());
	}
	return _imgManager.get();
}


ImageManager::ImageManager()
{
	// EMPTY
}

ImageManager::~ImageManager()
{
	ClearAllImages(); // clean up 
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ResourceHandle<Image> ImageManager::UploadImage(STRING & _name, Image * _image)
{
	ResourceHandle<Image> result(-1);

	// Check if the resource name is already in use
	result = _imageResources.Get(_name);
	if (!result.IsNull()) {
		LOG->ConsoleError("ERROR: Image named '" + _name + "' is already in use");
		return result;
	}

	result = _imageResources.Add(_name, _image);
	return result;
}

ResourceHandle<Image> ImageManager::UploadFile(STRING& _filePath, STRING& _name) 
{
	ResourceHandle<Image> result(-1);

	// Check if the resource name is already in use
	result = _imageResources.Get(_name);
	if (!result.IsNull()) {
		LOG->ConsoleError("ERROR: Image named '" + _name + "' is already in use");
		return result;
	}

	Image* img = new SdlImage(_filePath);
	img->SetName(_name);
	result = _imageResources.Add(_name, img);
	return result;
}

void ImageManager::DeleteImage(STRING & _name)
{
	_imageResources.Remove(_name);
}

void ImageManager::ClearAllImages()
{
	_imageResources.EmptyResourceMap();
}

ResourceHandle<Image> ImageManager::GetImageHandle(STRING & _name)
{
	return _imageResources.Get(_name);
}

Image* ImageManager::GetImage(ResourceHandle<Image>& _handle)
{
	return _imageResources.Get(_handle);
}

Image* ImageManager::GetImage(STRING & _name)
{
	Image* result = nullptr;
	ResourceHandle<Image> handle = _imageResources.Get(_name);

	if (handle.IsNull()) {
		LOG->ConsoleError("ERROR: Image named '" + _name + "' does not exist in ImageManager");
		return result;
	}
	result = ImageManager::GetImage(handle);
	return result;
}
