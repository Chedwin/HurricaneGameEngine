#include "Camera.h"
#include "HurricaneProperties.h"
#include "ShaderProgram.h"
#include "StandardShader.h"
#include "InputHandler.h"
#include "Game.h"


Camera::Camera(Scene* sc) : GameObject(sc)
{
	gameObject = this;
	AddTag("Camera");
}


Camera::~Camera()
{
	// EMPTY
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::CalculateCameraMatrix() 
{
	 // empty
}

void Camera::Update(const hFLOAT _deltaTime)
{
	// Empty
}

void Camera::Render() 
{
	hFLOAT winWidth = H_PROPERTIES->GetVideoProperties()->screenWidth;
	hFLOAT winHeight = H_PROPERTIES->GetVideoProperties()->screenHeight;
	hFLOAT drawDis = H_PROPERTIES->GetVideoProperties()->drawDistance;

	_projectionMatrix = glm::perspective(45.0f, (hFLOAT)winWidth / winHeight, 0.1f, drawDis);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	StandardShader* ss = STANDARD_SHADER;

	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);
}