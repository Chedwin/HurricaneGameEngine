//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Oct 12, 2016
//
//*******************************//

#pragma once

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
	~Camera();

	void Init(hINT scrWidth, hINT scrHeight);
	void Update();

	inline void SetPosition(const VECTOR3& newPos) {
		_pos = newPos;
		_needsMatrixUpdate = true;
	}
	inline void SetScale(hFLOAT newScale) {
		_scale = newScale;
		_needsMatrixUpdate = true;
	}

	inline VECTOR3 GetCameraPos() const {
		return _pos;
	}
	inline hFLOAT GetScale() const {
		return _scale;
	}
	inline MATRIX4 GetCameraMatrix() const {
		return _cameraMatrix;
	}

private:
	VECTOR3 _pos;
	VECTOR3 _dir;
	VECTOR3 _up;

	MATRIX4 _cameraMatrix;
	MATRIX4 _orthoMatrix;

	hINT _screenWidth, _screenHeight;

	hFLOAT _scale;
	hBOOL _needsMatrixUpdate;
};

#endif