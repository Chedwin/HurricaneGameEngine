//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"
#include "ShaderProgramManager.h"

#include "Frustum.h"

class Level;

class Camera : public GameObject
{
public:
	//Camera(Level* _level);
	Camera();
	~Camera();


	virtual void Update(const hFLOAT _deltaTime) override;
	virtual void Render() override;

	void CalculateCameraMatrix();


	inline void SetPostion(const VEC3& newPos) {
		gameObject->transform.position = newPos;
	}
	inline void SetUp(const VEC3& newUp) {
		_up = newUp;
	}
	inline void SetDir(const VEC3& newDir) {
		_dir = newDir;
	}


	inline GLuint GetViewLocation() const {
		return _viewLocation;
	}
	inline GLuint GetProjLocation() const {
		return _projectionLocation;
	}

	

	inline void SetViewLocation(const GLuint _view) {
		_viewLocation = _view;
	}
	inline void SetProjLocation(const GLuint _proj) {
		_projectionLocation = _proj;
	}

	inline MATRIX4 GetViewMatrix() const {
		return _viewMatrix;
	}

	inline MATRIX4 GetProjectionMatrix() const {
		return _projectionMatrix;
	}

protected:
	VEC3 _dir, _up;

	MATRIX4 _projectionMatrix;
	MATRIX4 _viewMatrix;

	GLuint _viewLocation;
	GLuint _projectionLocation;
public:
	Frustum frustum;
};

#endif