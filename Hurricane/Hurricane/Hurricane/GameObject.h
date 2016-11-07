//*******************************//
//
// Name:			GameObject.h
// Description:		Basic definition and implemenetation for a base game object.
//					Note that it is possible to have an empty game object that can still interact with the game world.
//					Components attached to them affect their behaviour in the game.			
//
// Author:			Edwin Chen
// Special Thanks:  Mathieu Violette, James Sholdice, Nathan Senter
//
// Created:			Sep 30, 2016
// Last updated:	Nov 06, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "HMath.h"
#include "Component.h"
#include "Vertex.h"

//typedef std::string Tag;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class Level;

class GameObject {
public:
	GameObject();
	//GameObject(Level* _level);
	virtual ~GameObject();


	//virtual void PreRender() {}
	//virtual void Render();

	virtual void Update(const hFLOAT _deltaTime) {}


	void AddChild(GameObject* g) {}
	void RemoveChild(GameObject* g) {}

	void AddComponent(Component* c);
	hBOOL HasComponent(Component *c);
	template<class TYPE> TYPE* GetComponent();
	void RemoveComponent(Component* c) {}


	// Direction vectors
	//VEC3 Left();
	//VEC3 Forward();
	//VEC3 Right();
	
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
	// i.e. similiar to Unity's design
	GameObject* gameObject; 

	// Transform fields
	VEC3 pos;
	VEC3 scale;
	QUATERNION rot;

	GLuint buffer[1];
	Vertex vertices;
};


#endif