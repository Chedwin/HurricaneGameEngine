#include "Debug.h"
#include "GameObject.h"

#include "PhysicsEngine.h"

#include "Component.h"
#include "MeshComponent.h"
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
	RemoveAllChildren();
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
	if (childObjects.size() > 0) 
	{
		VECTOR(GameObject*)::iterator iter;
		for (iter = childObjects.begin(); iter != childObjects.end(); iter++)
		{
			delete *iter;
			*iter = nullptr;
		}
	}
	childObjects.clear();
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
// TRANSFORM

// Reset its own transform
// NOTE: children of this object don't get affected by this function
void GameObject::ResetTransform()
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}
	gameObject->transform.position = VEC3(0.0f, 0.0f, 0.0f);
	gameObject->transform.scale = VEC3(1.0f, 1.0f, 1.0f);
	//gameObject->transform.rotation = QUATERNION();
}

// Translate
void GameObject::Translate(const VEC3 & v)
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}
	gameObject->transform.position += v;

	for (auto iter = childObjects.begin(); iter != childObjects.end(); iter++) {
		(*iter)->Translate(v);
	}
}

// Scale
void GameObject::Scale(const VEC3& s) 
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}

	gameObject->transform.scale *= s;

	for (auto iter = childObjects.begin(); iter != childObjects.end(); iter++) {
		(*iter)->Scale(s);
	}
}

// Rotate w/ DEGREES
void GameObject::Rotate(const VEC3& r) 
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}

	//QUATERNION _rot = (QUATERNION(_rotation.x, Vec3::BasisX()) * QUATERNION(_rotation.y, Vec3::BasisY()) * QUATERNION(_rotation.z, Vec3::BasisZ())).NormalizeThis();
	QUATERNION rot = glm::normalize(QUATERNION(r.x, BASIS3X) * QUATERNION(r.y, BASIS3Y) * QUATERNION(r.z, BASIS3Z));

	gameObject->transform.rotation *= rot;

	//for (auto it = childObjects.begin(); it != childObjects.end(); it++) {
		////Children don't quite rotate at the right pace.
		//(*it)->Rotate(rot);
		//VEC3 newPos = (*it)->transform.position - position;
		//(*it)->Translate((Quat::rotate(_rot, newPos.Normalized()) * newPos.magnitude() + position) - (*it)->position);
	//}
}

// Rotate w/ QUATERNIONS
void GameObject::Rotate(const QUATERNION& q) 
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}


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

// UPDATE (PHYSICS STUFF)
void GameObject::Update(const hFLOAT _deltaTime)
{
	if (!PHYSICS->isPhysicsRunning) {
		return;
	}

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

//////////////////////////////////////////////////////////////////////////////////////////////////

// RENDERING

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
	MeshComponent* renderable = gameObject->GetComponent<MeshComponent>();

	if (renderable) {
		renderable->Render();
	}
}