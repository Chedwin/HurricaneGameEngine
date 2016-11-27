//*******************************//
//
// Name:			Camera.h
// Description:		Perspective camera that is used to view the game level.
//
// Author:			Edwin Chen
// Created:			Sep 28, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//


#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"

#include "Frustum.h"

class Scene;

class Camera : public GameObject
{
public:
	Camera(Scene* sc);
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



	inline MATRIX4 GetMatrix() const {
		return _projectionMatrix * _viewMatrix;
	}

protected:
	VEC3 _dir, _up;

	MATRIX4 _projectionMatrix;
	MATRIX4 _viewMatrix;


public:
	Frustum frustum;
	GLuint mvpLocation;
};

#endif