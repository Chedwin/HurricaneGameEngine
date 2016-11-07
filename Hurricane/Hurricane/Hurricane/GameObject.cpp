#include "Debug.h"
#include "GameObject.h"
#include "Component.h"

//GameObject::GameObject(Level* _level) : gameObject(this)
//{
//	SetEnabled(true);
//
//	level = _level;
//
//	if (level) {
//		// TODO: add this gameobject to level's vector of objects
//	}
//} 

GameObject::GameObject() : gameObject(this)
{
	SetEnabled(true);
}

GameObject::~GameObject()
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////

// COMPONENTS

void GameObject::AddComponent(Component * c)
{
	hBOOL checkComp = HasComponent(c);

	if (!checkComp)
	{
		components.push_back(c);
		return;
	}
}

hBOOL GameObject::HasComponent(Component *c) 
{
	if (components.size() > 0) 
	{
		for (int i = 0; i <= components.size(); i++) 
		{
			Component* temp = components[i];
			if (temp->compType == c->compType) 
			{
				return true;
			}
		}	
	}
	return false;
}

template<class TYPE> TYPE* GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		/*if (typeid(*components[i]).name() == typeid(TYPE).name())
			return (TYPE*)components[i];*/
		Component* cp = components[i];
		if (cp->compType = typeif(TYPE).name()) 
		{
			return (TYPE*)components[i];
		}
	}
	return nullptr;
}



//////////////////////////////////////////////////////////////////////////////////////////////////

// TAGS

void GameObject::AddTag(const STRING& _tag)
{
	hBOOL checkTag = HasTag(_tag);

	if (!checkTag) 
	{
		tags.push_back(_tag);
		return;
	}	
}

hBOOL GameObject::HasTag(const STRING& _tag)
{
	for (int i = 0; i <= tags.size(); i++)
	{
		if (tags[i] == _tag)
			return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

// RENDERING

//void GameObject::Render() 
//{
//
//}