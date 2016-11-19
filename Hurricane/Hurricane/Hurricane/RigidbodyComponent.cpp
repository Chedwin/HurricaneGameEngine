#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(GameObject * _g) 
	: Component(_g, COMPONENT_TYPE::Rigidbody)
{

}

RigidbodyComponent::~RigidbodyComponent()
{

}