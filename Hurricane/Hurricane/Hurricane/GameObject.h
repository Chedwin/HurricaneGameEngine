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

typedef std::string tag;

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	VECTOR(tag) tags;
	VECTOR(Component*) components;

	virtual void PreRender();
	virtual void Render();
	virtual void Update(const hFLOAT _deltaTime);

	void AddChild(GameObject*);
	void RemoveChild(GameObject*);

	void AddComponent(Component* c);
	void RemoveComponent(Component* c);
	

	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}
public:
	hBOOL isEnabled;
};


#endif