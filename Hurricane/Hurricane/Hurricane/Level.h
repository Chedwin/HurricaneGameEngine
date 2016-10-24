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

	virtual hBOOL InitLevel() { return true; }
	void RenderLevel();

	GLuint cameraLocation;

	VECTOR(GameObject*) levelGameObjects;

	void LevelRender();
	virtual void LevelUpdate(const hFLOAT _timeStep);

	//Sets the current camera
	void SetCamera(Camera * _c);

	//Will delete all gameObjects that have been flagged for deletion
	void LevelCleanUp();

public:
	Camera* camera;
};

#endif