//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once

#include <glew.h>
#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"

#ifndef CAMERA_H
#define CAMERA_H

class Level;

class Camera : public GameObject
{
public:
	Camera(Level* _level);
	//Camera(const VEC3& _start);
	~Camera();

	void Init(hINT scrWidth, hINT scrHeight);
	void Update(const hFLOAT _deltaTime);
	void ResetCamera();


	inline void SetPosition(const VEC3& newPos) {
		pos = newPos;
	}
	inline void SetScale(hFLOAT newScale) {
		_scale = newScale;
	}

	inline VEC3 GetCameraPos() const {
		return pos;
	}
	inline hFLOAT GetScale() const {
		return _scale;
	}

private:
	VEC3 _dir;
	VEC3 _up;

	MATRIX4 _viewMatrix;
	MATRIX4 _projectionMatrix;

	hINT _screenWidth, _screenHeight;

	hFLOAT _scale;
	hBOOL _needsMatrixUpdate;

	GLuint _viewMatLocation;
	GLuint _projMatLocation;
};

#endif