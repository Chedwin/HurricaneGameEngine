#pragma once

#include <Macro.h>
#include <HMath.h>
#include <Camera.h>
#include <Scene.h>


class FlyCamera : public Camera {
public:
	FlyCamera(Scene* sc);
	~FlyCamera();

	void Update(const hFLOAT _deltaTime) override final;
	void Render() override final;

public:
	hFLOAT horizontalAngle, verticalAngle;
	hFLOAT initialFOV;

	hFLOAT speed; // units per second
	hFLOAT mouseSpeed;


	hINT winWidth, winHeight;
};
