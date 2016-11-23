//*******************************//
//
// Name:			FlyCamera.h
// Description:		A type of camera that allows a developer to move freely inside of a game space.
//					Very important for debugging purposes.
//
// Author:			Edwin Chen
// Created:			Nov 06, 2016
// Last updated:	Nov 22, 2016
//
//*******************************//


#ifndef FLY_CAMERA_H
#define FLY_CAMERA_H

#include <SDL.h>

#include "Macro.h"
#include "HMath.h"
#include "Camera.h"

#define FLY_DEBUG_CAM FlyCamera::GetFlyCamera()

//class FlyCamera : public Camera {
//protected:
//	FlyCamera();
//	~FlyCamera();
//public:
//
//	// Prod
//	void MoveCamera(SDL_Event& _evnt);
//	void Update(const hFLOAT _deltaTime) final;
//	void Render() final;
//
//
//	static FlyCamera* GetFlyCamera();
//
//protected:
//	static UNIQUE_PTR(FlyCamera) _flyCam;
//	friend DEFAULT_DELETE(FlyCamera);
//public:
//	hFLOAT horizontalAngle, verticalAngle;
//	hFLOAT initialFOV;
//
//	hFLOAT speed; // units per second
//	hFLOAT mouseSpeed;
//
//
//	hINT winWidth, winHeight;
//};

#endif