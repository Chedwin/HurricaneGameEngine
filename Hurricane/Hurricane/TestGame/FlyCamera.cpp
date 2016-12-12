#include <Debug.h>
#include <Game.h>
#include <StandardShader.h>

#include "FlyCamera.h"

FlyCamera::FlyCamera(Scene* sc) : Camera(sc)
{
	gameObject = this; // remember to set the self pointer

	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFOV = 45.0f;

	mouseSpeed = 0.00001f;
	speed = 4.0f;

	winWidth = GAME->gameWindow->GetWidth();
	winHeight = GAME->gameWindow->GetHeight();
	SetName("FlyCamera");
}

FlyCamera::~FlyCamera()
{
	// EMPTY
}


//////////////////////////////////////////////////////////////////////////////////////////////


void FlyCamera::Update(const hFLOAT _deltaTime)
{
	VEC2 mousePos;

	//mousePos.x = INPUT->motionEvent.x;
	//mousePos.y = INPUT->motionEvent.y;

	mousePos.x = INPUT->GetMousePos().x;
	mousePos.y = INPUT->GetMousePos().y;

	Debug::ConsoleLog(VEC3(mousePos, 0));

	horizontalAngle += mouseSpeed * hFLOAT(winWidth / 2.0f - mousePos.x);
	verticalAngle += mouseSpeed * hFLOAT(winHeight / 2.0f - mousePos.y);

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


	if (INPUT->IsKeyDown(SDLK_w)) {
		gameObject->transform.position += _dir * _deltaTime * speed;	
	}
	else if (INPUT->IsKeyDown(SDLK_s)) {
		gameObject->transform.position -= _dir * _deltaTime * speed;	
	}
	else if (INPUT->IsKeyDown(SDLK_a)) {
		gameObject->transform.position -= right * _deltaTime * speed;
	}
	else if (INPUT->IsKeyDown(SDLK_d)) {
		gameObject->transform.position += right * _deltaTime * speed;
	}

}


void FlyCamera::Render() 
{
	_projectionMatrix = glm::perspective(initialFOV, (hFLOAT)winWidth / winHeight, 0.1f, 50.0f);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	StandardShader* ss = STANDARD_SHADER;

	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);
}