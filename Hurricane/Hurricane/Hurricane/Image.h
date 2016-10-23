//*******************************//
//
// Name:			Image.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 18, 2016
// Last updated:	Oct 23, 2016
//
//*******************************//

#pragma once

#include "Macro.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image 
{
public:
	// Create empty image with specified size
	Image(hINT _width, hINT _height) {}

	// Get image from filepath
	Image(STRING& _filePath) {}

	virtual ~Image() {}

	inline STRING GetName() const {
		return _imgName;
	}

	inline void SetName(STRING& name) {
		_imgName = name;
	}

	

protected:
	//Initialize an empty image to the indicated size.
	virtual hBOOL Init(hINT width, hINT height) = 0;

	// Initialize an image by reading it from a file. This will throw exceptions if any problems are encountered.
	virtual hBOOL Init(STRING& filePath) = 0;


	
protected:
	STRING _imgName;
	
};

#endif