#include "Camera.h"
#include "HurricaneProperties.h"
#include "ShaderProgram.h"
#include "StandardShader.h"


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

	//VEC3 camForward = glm::rotate(gameObject->transform.rotation, 0.0f, BASIS3Z);
	VEC3 camTarget = VEC3(0.0f, 0.0f, 0.0f);
	_dir = glm::normalize(gameObject->transform.position - camTarget);

	VEC3 up = VEC3(0, 1, 0);
	VEC3 camRight = glm::normalize(glm::cross(up, _dir));

	_up = glm::cross(_dir, camRight);

	_viewMatrix = glm::lookAt(gameObject->transform.position, _dir, _up);

}

void Camera::Update(const hFLOAT _deltaTime)
{
	CalculateCameraMatrix();

	StandardShader* ss = STANDARD_SHADER;
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);
}

void Camera::Render() 
{
	// EMPTY
}