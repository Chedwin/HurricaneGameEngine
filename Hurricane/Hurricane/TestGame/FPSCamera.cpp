#include "FPSCamera.h"
#include <Debug.h>

FPSCamera::FPSCamera() : Camera()
{
	GameObject::pos = VEC3(2, 1, -1);
	horizontalAngle = 3.14f;
	verticalAngle = 0.0f;
	initialFOV = 60.0f;

}

FPSCamera::~FPSCamera()
{
	// EMPTY
}



//////////////////////////////////////////////////////////////////////////////////////////////

void FPSCamera::Update(const hFLOAT _deltaTime)
{
	VEC3 direction(0.0f, 0.0f, 0.0f);
	VEC3 up(0.0f, 0.0f, 1.0f);

	_projectionMatrix = glm::perspective(initialFOV, 1.0f, 0.1f, 100.0f);
	_viewMatrix = glm::lookAt(GameObject::pos, VEC3(0,0,0), up);

	//COUT << position.x << " " << position.y << ENDL;
}

void FPSCamera::MoveCamera(SDL_Event & _evnt)
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
