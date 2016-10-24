//*******************************//
//
// Name:			GameObject.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Sep 30, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "Component.h"
#include "HMath.h"

typedef std::string Tag;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class Level;

class GameObject {
public:
	GameObject() {}
	GameObject(Level* _level);
	virtual ~GameObject();


	virtual void PreRender() {}
	virtual void Render() {}
	virtual void Update(const hFLOAT _deltaTime) {}

	void AddChild(GameObject*) {}
	void RemoveChild(GameObject*) {}

	void AddComponent(Component* c);
	void RemoveComponent(Component* c) {}

	// Direction vectors
	//VEC3 Left();
	//VEC3 Forward();
	//VEC3 Right();
	
	hBOOL HasTag(Tag _tag);
	
	inline hBOOL CheckEnabled() const {
		return isEnabled;
	}
	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}
public:
	VECTOR(Tag) tags;
	VECTOR(Component*) components;

	hBOOL isEnabled;
	Level* level;

	// Transform fields
	VEC3 pos;
	VEC3 scale;
	QUATERNION rot;

};


#endif