//*******************************//
//
// Name:			GameObject.h
// Description:		Basic definition and implemenetation for a base game object.
//					Note that it is possible to have an empty game object that can still interact with the game world.
//					Components attached to them affect their behaviour in the game.	
//					i.e. Very similiar to Unity's design
//
// Author:			Edwin Chen
// Special Thanks:  Mathieu Violette, James Sholdice, Nathan Senter, Unity
//
// Created:			Sep 30, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Macro.h"
#include "HMath.h"
#include "Component.h"
#include "Transform.h"

class Level;

class GameObject {
public:
	GameObject();
	//explicit GameObject(Level* _level);
	virtual ~GameObject();

	// TO BE OVERRIDED BY DERIVED CLASSES
	virtual void Update(const hFLOAT _deltaTime) {}
	virtual void Render() {}


	void AddChild(GameObject* g) {}
	void RemoveChild(GameObject* g) {}

	void AddComponent(Component* c);
	hBOOL HasComponent(Component *c);
	void RemoveComponent(Component* c) {}
	template<class TYPE> TYPE* GetComponent();

	
	void AddTag(const STRING& _tag);
	hBOOL HasTag(const STRING& _tag);
	
	inline hBOOL CheckEnabled() const {
		return isEnabled;
	}
	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}



public:
	VECTOR(STRING) tags;
	VECTOR(Component*) components;
	VECTOR(GameObject*) childObjects;

	hBOOL isEnabled;
	Level* level;

	// pointer to itself
	GameObject* gameObject; 

	// Transform fields
	Transform transform;
};


#endif