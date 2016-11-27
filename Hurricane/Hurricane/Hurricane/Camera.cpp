#include "Camera.h"
#include "HurricaneProperties.h"


Camera::Camera(Scene* sc) : GameObject(sc)
{
	gameObject = this;
}


Camera::~Camera()
{
	// EMPTY
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::CalculateCameraMatrix() 
{
	HurricaneProperties* gp = H_PROPERTIES;

	_projectionMatrix = glm::perspective(45.0f, gp->GetVideoProperties()->AspectRatio(), 0.1f, gp->GetVideoProperties()->drawDistance);
	_viewMatrix = glm::lookAt(gameObject->transform.position, VEC3(0, 0, 0), VEC3(0, 0, 1));
}

void Camera::Update(const hFLOAT _deltaTime)
{
}

void Camera::Render() 
{
	MATRIX4 mvp = _projectionMatrix * _viewMatrix * MATRIX4(1.0f);
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
}