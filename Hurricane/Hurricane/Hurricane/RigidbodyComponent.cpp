#include "RigidbodyComponent.h"
#include "PhysicsEngine.h"


RigidbodyComponent::RigidbodyComponent(GameObject * _g)
	: Component(_g, COMPONENT_TYPE::Rigidbody)
{
	InitBody();
}


void RigidbodyComponent::InitBody()
{
	mass = 1.0f;

	// Vec3(0,0,0)
	centerOfMass = ORIGIN;
	velocity = ORIGIN;
	accel = ORIGIN;

	// Insert this component into the physics engine
	PhysicsEngine* ph = PHYSICS;
	ph->physicsObjects.push_back(this);
}


RigidbodyComponent::~RigidbodyComponent()
{
	PhysicsEngine* phy = PHYSICS;

	for (auto it = phy->physicsObjects.begin(); it != phy->physicsObjects.end(); it++) 
	{
		RigidbodyComponent* temp = (*it);
		if (temp == this) {
			phy->physicsObjects.erase(it);
			break;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RigidbodyComponent::AddForce(VEC3 _force) {
	accel += _force / mass;
}