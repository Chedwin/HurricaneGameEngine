#include "Camera.h"
#include "HurricaneProperties.h"
#include "ShaderProgram.h"
#include "StandardShader.h"
#include "InputHandler.h"
#include "Game.h"


Camera::Camera(Scene* sc) : GameObject(sc)
{
	gameObject = this;

	winWidth  = GAME->gameWindow->GetWidth();
	winHeight = GAME->gameWindow->GetHeight();

	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFOV = 45.0f;

	mouseSpeed = 0.000001f;
	speed = 4.0f;
	
	//frustum.WindowResized(initialFOV, winWidth / winHeight, 0.1f, 50.0f);
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
	//CalculateCameraMatrix();

	// INPUT UPDATING
	VEC2 mousePos;

	InputHandler* input = INPUT;
	mousePos.x = input->motionEvent.x;
	mousePos.y = input->motionEvent.y;

	//horizontalAngle += mouseSpeed * hFLOAT(winWidth / 2.0f - mousePos.x);
	//verticalAngle += mouseSpeed * hFLOAT(winHeight / 2.0f - mousePos.y);

	 // Update direction
	_dir = VEC3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	
	// Up vector
	_up = glm::cross(right, _dir);


	// Keyboard
	if (input->IsKeyDown(SDLK_w)) {
		gameObject->transform.position += _dir * _deltaTime * speed;
	}
	else if (input->IsKeyDown(SDLK_s)) {
		gameObject->transform.position -= _dir * _deltaTime * speed;
	}
	else if (input->IsKeyDown(SDLK_a)) {
		gameObject->transform.position -= right * _deltaTime * speed;
	}
	else if (input->IsKeyDown(SDLK_d)) {
		gameObject->transform.position += right * _deltaTime * speed;
	}

	//frustum.CameraChanged(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	/// 
}

void Camera::Render() 
{
	_projectionMatrix = glm::perspective(initialFOV, (hFLOAT)winWidth / winHeight, 0.1f, 50.0f);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	StandardShader* ss = STANDARD_SHADER;

	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);
}