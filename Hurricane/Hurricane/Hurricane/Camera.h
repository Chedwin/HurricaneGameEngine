//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Nov 01, 2016
//
//*******************************//

#pragma once

#include <glew.h>
#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"
#include "ShaderProgramManager.h"

#ifndef CAMERA_H
#define CAMERA_H

class Level;

class Camera 
	//: public GameObject
{
public:
	//Camera(Level* _level);
	Camera();
	Camera(const VEC3& pos, hFLOAT fov, hFLOAT aspect, hFLOAT zNear, hFLOAT zFar);
	~Camera();

	void Init(hINT scrWidth, hINT scrHeight);
	void Update(const hFLOAT _deltaTime);
	void ResetCamera();
	void LookAt(VEC3& pos, VEC3& dir, VEC3& up);

	inline void SetPos(const VEC3& newPos) {
		_pos = newPos;
	}
	inline void SetUp(const VEC3& newUp) {
		_up = newUp;
	}
	inline void SetDir(const VEC3& newDir) {
		_dir = newDir;
	}

	inline void SetScale(hFLOAT newScale) {
		_scale = newScale;
	}

	inline VEC3 GetCameraPos() const {
		return _pos;
	}
	inline hFLOAT GetScale() const {
		return _scale;
	}
	inline MATRIX4 GetCameraMatrix() const {
		return _cameraMatrix;
	}

	inline MATRIX4 GetViewProjection() const {
		return _projectionMatrix * glm::lookAt(_pos, _dir, _up);
	}

private:
	VEC3 _dir,_up, _pos;

	MATRIX4 _projectionMatrix;
	MATRIX4 _cameraMatrix;
	MATRIX4 _modelView;

	hINT _screenWidth, _screenHeight;

	hFLOAT _scale;
	hBOOL _needsMatrixUpdate;

	GLuint _cameraLocation;
	GLuint _projectionLocation;


	// Model View Projection 
	MATRIX4 _MVPmat;
	GLuint _mvpLoc; 
};

#endif