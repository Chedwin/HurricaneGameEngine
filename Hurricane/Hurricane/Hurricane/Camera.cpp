#include "Camera.h"
#include "HurricaneProperties.h"

Camera::Camera(Level* _level) : GameObject(_level) 
{
	ResetCamera();
}

//Camera::Camera() : GameObject()
//{
//	pos = _start;
//}

Camera::~Camera()
{
}

void Camera::Init(hINT scrWidth, hINT scrHeight)
{
	_screenWidth = scrWidth;
	_screenHeight = scrHeight;
	//_projectionMatrix = glm::ortho(0.0f, (hFLOAT)_screenWidth, 0.0f, (hFLOAT)_screenHeight);
	_projectionMatrix = 
		glm::perspective(60.0f, (float)H_PROPERTIES->GetVideoProperties()->screenWidth / (float)H_PROPERTIES->GetVideoProperties()->screenHeight, 0.1f, 10.0f);
}

void Camera::Update(const hFLOAT _deltaTime)
{
	VEC3 translateVec(-pos.x, -pos.y, 0.0f);
	_viewMatrix = glm::translate(_projectionMatrix, translateVec);

	VEC3 scaleVec(_scale, _scale, 0.0f);
	_viewMatrix = glm::scale(_viewMatrix, scaleVec);
	_needsMatrixUpdate = false;
}

//void Camera::Update()
//{
//	if (_needsMatrixUpdate)
//	{
//		VEC3 translateVec(-pos.x, -pos.y, 0.0f);
//		_viewMatrix = glm::translate(_projectionMatrix, translateVec);
//
//		VEC3 scaleVec(_scale, _scale, 0.0f);
//		_viewMatrix = glm::scale(_viewMatrix, scaleVec);
//		_needsMatrixUpdate = false;
//	}
//
//
//}

void Camera::ResetCamera()
{
	pos = VEC3(0.0f, 0.0f, 0.0f);
	_dir = VEC3(0.0f, 0.0f, 0.0f);
	_up = VEC3(0.0f, 0.0f, 0.0f);

	_viewMatrix = MATRIX4(1.0f);
	_scale = 1.0f;
	//_needsMatrixUpdate = true;
	_screenWidth = 0;
	_screenHeight = 0;
	_projectionMatrix = MATRIX4(1.0f);
}
