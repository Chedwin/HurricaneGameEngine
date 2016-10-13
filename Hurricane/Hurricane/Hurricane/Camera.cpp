#include "Camera.h"

Camera::Camera(Level* _level) : GameObject(_level) 
{
	_pos = VECTOR3(0.0f, 0.0f, 0.0f);
	_cameraMatrix = MATRIX4(1.0f);
	_scale = 1.0f;
	_needsMatrixUpdate = true;
	_screenWidth = 0;
	_screenHeight = 0;
	_orthoMatrix = MATRIX4(1.0f);
}

Camera::~Camera()
{
}

void Camera::Init(hINT scrWidth, hINT scrHeight)
{
	_screenWidth = scrWidth;
	_screenHeight = scrHeight;
	_orthoMatrix = glm::ortho(0.0f, (hFLOAT)_screenWidth, 0.0f, (hFLOAT)_screenHeight);
}

void Camera::Update()
{
	if (_needsMatrixUpdate)
	{
		VECTOR3 translateVec(-_pos.x, -_pos.y, 0.0f);
		_cameraMatrix = glm::translate(_orthoMatrix, translateVec);

		VECTOR3 scaleVec(_scale, _scale, 0.0f);
		_cameraMatrix = glm::scale(_cameraMatrix, scaleVec);
		_needsMatrixUpdate = false;
	}


}