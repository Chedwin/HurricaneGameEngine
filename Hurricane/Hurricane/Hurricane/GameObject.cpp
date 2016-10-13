#include "GameObject.h"

GameObject::GameObject(Level* _level)
{
	SetEnabled(true);

	level = _level;

	if (level) {
		// TODO: add this gameobject to level's vector of objects
	}
} 

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component * c)
{
	components.push_back(c);
}
