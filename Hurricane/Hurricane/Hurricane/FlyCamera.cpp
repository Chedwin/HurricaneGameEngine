#include "FlyCamera.h"
#include "Debug.h"
#include "Game.h"

UNIQUE_PTR(FlyCamera) FlyCamera::_flyCam(nullptr);

FlyCamera* FlyCamera::GetFlyCamera() {
	if (_flyCam.get() == nullptr) {
		_flyCam.reset(new FlyCamera());
	}
	return _flyCam.get();
}


FlyCamera::FlyCamera() : Camera()
{
	gameObject = this; // remember to set the self pointer

	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFOV = 45.0f;

	mouseSpeed = 0.0001f;
	speed = 4.0f;

	winWidth = GAME->gameWindow->GetWidth();
	winHeight = GAME->gameWindow->GetHeight();
}

FlyCamera::~FlyCamera()
{
	// EMPTY
}



//////////////////////////////////////////////////////////////////////////////////////////////

void FlyCamera::MoveCamera(SDL_Event & _evnt)
{
	VEC2 mousePos;

	switch (_evnt.type) {
	case SDL_MOUSEMOTION:
		mousePos.x = _evnt.motion.x;
		mousePos.y = _evnt.motion.y;

		horizontalAngle += mouseSpeed * hFLOAT(winWidth / 2.0f - mousePos.x);
		verticalAngle += mouseSpeed * hFLOAT(winHeight / 2.0f - mousePos.y);

		break;
	}

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

	switch(_evnt.type) {
	case SDL_KEYDOWN:
		switch (_evnt.key.keysym.sym) {
		case SDLK_w:
			gameObject->transform.position += _dir * GAME->GetDeltaTime() * speed;
			break;
		case SDLK_s:
			gameObject->transform.position -= _dir * GAME->GetDeltaTime() * speed;
			break;
		case SDLK_a:
			gameObject->transform.position -= right * GAME->GetDeltaTime() * speed;
			break;
		case SDLK_d:
			gameObject->transform.position += right * GAME->GetDeltaTime() * speed;
			break;

		case SDLK_z:
			glEnable(GL_DEPTH_TEST);
			break;
		case SDLK_u:
			glDisable(GL_DEPTH_TEST);
			break;
		}
	case SDL_KEYUP:
		break;
	}


}


void FlyCamera::Update(const hFLOAT _deltaTime)
{
	frustum.CameraChanged(transform.position, gameObject->transform.position + _dir, _up);
	_projectionMatrix = glm::perspective(initialFOV, 1.0f, 0.1f, 100.0f);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);
}


void FlyCamera::Render() 
{
	//glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, &_projectionMatrix[0][0]);
	//glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, &_viewMatrix[0][0]);
}