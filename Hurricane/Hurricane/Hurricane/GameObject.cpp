#include "GameObject.h"

GameObject::GameObject()
{
	SetEnabled(true);
} 

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component * c)
{
	components.push_back(c);
}
