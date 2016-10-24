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


//////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::AddComponent(Component * c)
{
	components.push_back(c);
}

//VEC3 GameObject::Left()
//{
//
//}
//
//VEC3 GameObject::Forward()
//{
//
//}
//
//VEC3 GameObject::Right()
//{
//	
//}

hBOOL GameObject::HasTag(Tag _tag)
{
	for (int i = 0; i <= tags.size(); i++)
	{
		if (tags[i] == _tag)
			return true;
	}
	return false;
}
