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
	//HurricaneProperties* gp = H_PROPERTIES;

	//glm::mat4 m = glm::perspective(45.0f, gp->GetVideoProperties()->AspectRatio(), 0.1f, gp->GetVideoProperties()->drawDistance);

	//VEC3 camForward = glm::rotate(transform.rotation, VEC3(0.0f, 0.0f, 1.0f));

	//VEC3 forawrd = gameObject->transform.position + camForward;

	//VEC3 _camUp = glm::rotate(transform.rotation, VEC3(0, 1, 0)).Normalized();
	//glm::mat4 m2 = glm::lookAt(VEC3(transform.position.x, transform.position.y, transform.position.z), VEC3(forawrd.x, forawrd.y, forawrd.z), VEC3(_camUp.x, _camUp.y, _camUp.z));

	////Get array pointer to glm matrix
	//const float *mSource  = (const float*)glm::value_ptr(m);
	//const float *m2Source = (const float*)glm::value_ptr(m2);

	//for (int i = 0; i < 16; i++)
	//{
	//	projectionMatrix.values[i] = mSource[i];
	//	viewMatrix.values[i] = m2Source[i];
	//}
}

void Camera::Update(const hFLOAT _deltaTime)
{
}

void Camera::Render() 
{
	
}