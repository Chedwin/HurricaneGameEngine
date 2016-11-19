#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(GameObject * g)
	: Component(g, COMPONENT_TYPE::Collider)
{
	// EMPTY
}

ColliderComponent::~ColliderComponent()
{
	// EMPTY
}