//*******************************//
//
// Name:			Level.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Sep 27, 2016
// Last updated:	Oct 11, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "Camera.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level 
{
public:
	Level();
	~Level();

	void Init();
	void Render();

	GLuint cameraLocation;

	VECTOR(GameObject*) levelGameObjects;

public:
	Camera* camera;
};

#endif