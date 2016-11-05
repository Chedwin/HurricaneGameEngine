//*******************************//
//
// Name:			GameObject.h
// Description:		
//
// Author:			Edwin Chen, Mathieu Violette, James Sholdice, Nathan Senter
// Created:			Sep 30, 2016
// Last updated:	Oct 29, 2016
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


	virtual void PreRender() {}
	virtual void Render();
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

	GameObject* gameObject; // pointer to itself

	// Transform fields
	VEC3 pos;
	VEC3 scale;
	QUATERNION rot;

	GLuint buffer[1];
	Vertex vertices;
};


#endif