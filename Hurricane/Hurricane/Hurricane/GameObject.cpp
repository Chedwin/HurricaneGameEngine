#include "Debug.h"
#include "GameObject.h"

#include "Component.h"
#include "RenderableComponent.h"
#include "LightComponent.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

// CONSTRUCTOR(S) / DESTRUCTOR
GameObject::GameObject() : gameObject(this)
{
	SetName("MyGameObject");
	SetEnabled(true);
	componentList.reserve(sizeof(COMPONENT_TYPE));
}

GameObject::GameObject(const STRING& name) : gameObject(this)
{
	SetName(name);
	SetEnabled(true);
	componentList.reserve(sizeof(COMPONENT_TYPE));
}

GameObject::~GameObject()
{
	// TODO: Destroy and clean up components and other game objects
	if (componentList.size() > 0)
	{
		for (int i = 0; i < componentList.size(); i++) 
		{
			//switch (componentList[i]->compType) {
			//case COMPONENT_TYPE::Renderable:
			//	
			//	break;
			//case COMPONENT_TYPE::Light:
			//	break;
			//case COMPONENT_TYPE::Rigidbody:
			//	break;
			//case COMPONENT_TYPE::Collider:
			//	break;
			//}

			delete componentList[i];
			componentList[i] = nullptr;
		}
	}
	componentList.clear();

	// TODO: Destroy all child objects
	// The root node of a scene will signal everyone to destroy themselves
	if (childObjects.size() > 0) 
	{
		for (GameObject* g : childObjects) 
		{
			delete g;
			g = nullptr;
		}
	}
	childObjects.clear();
}



//////////////////////////////////////////////////////////////////////////////////////////////////

// CHILDREN GAME OBJECTS
// Helpful when building scene graph

void GameObject::AddChild(GameObject * g)
{
	childObjects.push_back(g);
}

void GameObject::RemoveChild(GameObject * g)
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = childObjects.begin(); iter != childObjects.end(); iter++) 
	{
		if (*iter == g) 
		{
			delete *iter;
			*iter = nullptr;
			return;
		}
	}
	Debug::ConsoleError("Game object is not a child", __FILE__, __LINE__);
}

void GameObject::RemoveAllChildren() 
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
	{
		delete *iter;
		*iter = nullptr;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// ATTACHABLE COMPONENTS

void GameObject::AddComponent(Component* c)
{
	hBOOL checkComp = HasComponent(c);

	if (!checkComp)
	{
		componentList.push_back(c);
		//compMap.insert(std::make_pair(typeid(c).name(), c));
		return;
	}
}

hBOOL GameObject::HasComponent(Component* c)
{
	if (componentList.size() > 0) 
	{		
		for (int i = 0; i < componentList.size(); i++)
		{
			Component* temp = componentList[i];
			if (temp->compType == c->compType)
			{
				return true;
			}
		}
	}
	//if (compMap.size() > 0)
	//{
	//	auto name = typeid(c).name();
	//	if (compMap[typeid(c).name()]) {
	//		return true;
	//	}
	//}
	return false;
}

// GET COMPONENT
// see component for refernce of component types
template<typename TYPE> TYPE* GameObject::GetComponent()
{
	for (int i = 0; i < componentList.size(); i++)
	{
		if (typeid(*componentList[i]).name() == typeid(TYPE).name()) 
		{
			return dynamic_cast<TYPE*>(componentList[i]);
			//return (TYPE*)componentList[i];	
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
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == _tag)
			return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATE
void GameObject::Update(const hFLOAT _deltaTime)
{
	RigidbodyComponent* rbc = gameObject->GetComponent<RigidbodyComponent>();

	if (rbc) {
		//TODO: 
		//rbc-> 
	}

	ColliderComponent* cc = gameObject->GetComponent<ColliderComponent>();

	if (cc) {
		// TODO:
		//cc-> 
	}
}

// PRE RENDER
void GameObject::PreRender() 
{
	LightComponent* lc = gameObject->GetComponent<LightComponent>();
	if (lc) {
		lc->PushLight();
	}
}

// RENDERING
void GameObject::Render()
{
	// Render THIS object
	RenderableComponent* renderable = gameObject->GetComponent<RenderableComponent>();

	if (renderable) {
		renderable->Render();
	}
}