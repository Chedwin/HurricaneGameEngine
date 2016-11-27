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
}


Camera::~Camera()
{
	// EMPTY
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void Camera::CalculateCameraMatrix() 
{
	//HurricaneProperties* gp = H_PROPERTIES;
	//_projectionMatrix = glm::perspective(45.0f, gp->GetVideoProperties()->AspectRatio(), 0.1f, gp->GetVideoProperties()->drawDistance);

	////VEC3 camForward = glm::rotate(gameObject->transform.rotation, 0.0f, BASIS3Z);
	//VEC3 camTarget = VEC3(0.0f, 0.0f, 0.0f);
	//_dir = glm::normalize(gameObject->transform.position - camTarget);

	//VEC3 up = VEC3(0, 1, 0);
	//VEC3 camRight = glm::normalize(glm::cross(up, _dir));

	//_up = glm::cross(_dir, camRight);


	//glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 up2 = glm::vec3(0.0f, 1.0f, 0.0f);
	//_viewMatrix = glm::lookAt(VEC3(2,2,2), dir, up2);


	//VEC2 mousePos;



	//
	//	switch (_evnt.type) {
	//	case SDL_MOUSEMOTION:
	//		mousePos.x = _evnt.motion.x;
	//		mousePos.y = _evnt.motion.y;
	//
	//		horizontalAngle += mouseSpeed * hFLOAT(winWidth / 2.0f - mousePos.x);
	//		verticalAngle += mouseSpeed * hFLOAT(winHeight / 2.0f - mousePos.y);
	//
	//		break;
	//	}
	//
	//	// Update direction
	//	_dir = VEC3(
	//		cos(verticalAngle) * sin(horizontalAngle),
	//		sin(verticalAngle),
	//		cos(verticalAngle) * cos(horizontalAngle)
	//	);
	//
	//	// Right vector
	//	glm::vec3 right = glm::vec3(
	//		sin(horizontalAngle - 3.14f / 2.0f),
	//		0,
	//		cos(horizontalAngle - 3.14f / 2.0f)
	//	);
	//
	//	// Up vector
	//	_up = glm::cross(right, _dir);
	//
	//	switch(_evnt.type) {
	//	case SDL_KEYDOWN:
	//		switch (_evnt.key.keysym.sym) {
	//		case SDLK_w:
	//			gameObject->transform.position += _dir * _deltaTime * speed;
	//			break;
	//		case SDLK_s:
	//			gameObject->transform.position -= _dir * _deltaTime * speed;
	//			break;
	//		case SDLK_a:
	//			gameObject->transform.position -= right * _deltaTime * speed;
	//			break;
	//		case SDLK_d:
	//			gameObject->transform.position += right * _deltaTime * speed;
	//			break;
	//
	//		case SDLK_z:
	//			glEnable(GL_DEPTH_TEST);
	//			break;
	//		case SDLK_u:
	//			glDisable(GL_DEPTH_TEST);
	//			break;
	//		}
	//	case SDL_KEYUP:
	//		break;
	//	}
}

void Camera::Update(const hFLOAT _deltaTime)
{
	//CalculateCameraMatrix();

	// INPUT UPDATING
	VEC2 mousePos;

	InputHandler* input = INPUT;
	mousePos.x = input->motionEvent.x;
	mousePos.y = input->motionEvent.y;

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

	/// 
	/*_projectionMatrix = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	StandardShader* ss = STANDARD_SHADER;
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);*/
}

void Camera::Render() 
{
	_projectionMatrix = glm::perspective(60.0f, 1.0f, 0.1f, 100.0f);
	_viewMatrix = glm::lookAt(gameObject->transform.position, gameObject->transform.position + _dir, _up);

	StandardShader* ss = STANDARD_SHADER;
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->projection_Location, 1, GL_FALSE, &_projectionMatrix[0][0]);
	glProgramUniformMatrix4fv(ss->GetProgramID(), ss->view_Location, 1, GL_FALSE, &_viewMatrix[0][0]);
}