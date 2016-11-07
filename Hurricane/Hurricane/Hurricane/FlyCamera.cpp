#include "FlyCamera.h"
#include "Debug.h"

UNIQUE_PTR(FlyCamera) FlyCamera::_flyCam(nullptr);

FlyCamera* FlyCamera::GetFlyCamera() {
	if (_flyCam.get() == nullptr) {
		_flyCam.reset(new FlyCamera());
	}
	return _flyCam.get();
}


FlyCamera::FlyCamera() : Camera()
{
	GameObject::pos = VEC3(2, 1, -1);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFOV = 60.0f;
}

FlyCamera::~FlyCamera()
{
	// EMPTY
}



//////////////////////////////////////////////////////////////////////////////////////////////

void FlyCamera::Update(const hFLOAT _deltaTime)
{
	VEC3 direction(0.0f, 0.0f, 0.0f);
	VEC3 up(0.0f, 0.0f, 1.0f);

	_projectionMatrix = glm::perspective(initialFOV, 1.0f, 0.1f, 100.0f);
	_viewMatrix = glm::lookAt(GameObject::pos, VEC3(0, 0, 0), up);

	glUniformMatrix4fv(_projectionLocation, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glUniformMatrix4fv(_viewLocation, 1, GL_FALSE, &_viewMatrix[0][0]);
}

void FlyCamera::MoveCamera(SDL_Event & _evnt)
{
	switch (_evnt.type) {
	case SDL_KEYDOWN:
		switch (_evnt.key.keysym.sym) {
		case SDLK_a:
			GameObject::pos -= VEC3(0.3f, 0.3f, 0.0f);
			Debug::ConsoleLog("Slide to the left");
			break;
		case SDLK_d:
			GameObject::pos += VEC3(0.3f, 0.3f, 0.0f);
			Debug::ConsoleLog("Slide to the right");
			break;
		}
	case SDL_KEYUP:
		break;
	}
}
