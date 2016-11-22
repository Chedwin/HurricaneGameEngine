//*******************************//
//
// Name:			GameObject.h
// Description:		Basic definition and implemenetation for a base game object.
//					Note that it is possible to have an empty game object that can still interact with the game world.
//					Components attached to them affect their behaviour in the game.	
//					i.e. Very similiar to Unity's design
//
// Author:			Edwin Chen
// Special Thanks:  Mathieu Violette, James Sholdice, Nathan Senter, Unity, Aiden Dearing, House Yokeswaran, Mark Seaman
//
// Created:			Sep 30, 2016
// Last updated:	Nov 21, 2016
//
//*******************************//


#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include "Macro.h"
#include "HMath.h"
#include "Component.h"
#include "Transform.h"
#include "GameObjectScript.h"

class Scene;

class GameObject {
public:
	GameObject(Scene* sc);
	explicit GameObject(Scene* sc, const STRING& name);
	virtual ~GameObject();

	// "CAN" BE OVERRIDEN BY DERIVED CLASSES
	virtual void Update(const hFLOAT _deltaTime);
	virtual void PreRender();
	virtual void Render();


	void AddChild(GameObject* g);
	void RemoveChild(GameObject* g);
	void RemoveChild(const STRING& n);
	void ClearAllChildren();

	GameObject* GetChild(const STRING& name);
	GameObject* GetChild(GameObject* g);

	void AddComponent(Component* c);
	hBOOL HasComponent(Component* c);
	void RemoveComponent(Component* c) {}


	// GetComponent template function
	// i.e. similiar to Unity;
	template<typename TYPE> TYPE* GetComponent();

	void ResetTransform();

	void Translate(const VEC3& v);
	void Scale(const VEC3& s);

	void Rotate(const VEC3& r);
	void Rotate(const QUATERNION& q);

	void AddTag(const STRING& _tag);
	hBOOL HasTag(const STRING& _tag);
	
	// Scripting
	void AttachScript(GameObjectScript* s);
	void DetachScript();


	inline hBOOL CheckEnabled() const {
		return isEnabled;
	}
	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}

	inline STRING GetName() const {
		return _name;
	}
	inline void SetName(const STRING& n) {
		_name = n;
	}

protected:
	STRING _name;
public:
	VECTOR(STRING) tags;
	VECTOR(Component*) componentList;

	UNORDERED_MAP(STRING, Component*) compMap;

	VECTOR(GameObject*) childObjects;

	hBOOL isEnabled;

	// pointer to itself (Unity-like)
	GameObject* gameObject; 

	// Transform fields
	Transform transform;

	// Scripting behaviour 
	GameObjectScript* attachedScript;

	// Which scene is it in?
	Scene* scene;
};


#endif