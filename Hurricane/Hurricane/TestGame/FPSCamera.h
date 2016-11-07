#pragma once 

#include <SDL.h>
#include <Macro.h>
#include <HMath.h>

#include <Camera.h>

class FPSCamera : public Camera {
public:
	FPSCamera();
	~FPSCamera();

	void Update(const hFLOAT _deltaTime);
	void MoveCamera(SDL_Event& _evnt);


public:
	hFLOAT horizontalAngle, verticalAngle;
	hFLOAT initialFOV;

	hFLOAT speed; // units per second
	hFLOAT mouseSpeed;
};