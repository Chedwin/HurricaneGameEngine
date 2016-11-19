//*******************************//
//
// Name:			Component.h
// Description:		Defines a basic component class for different component types.
//
// Author:			Edwin Chen, Mathieu Violette, James Sholdice, Nathan Senter
// Created:			Sep 30, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//


#ifndef COMPONENT_H
#define COMPONENT_H

#include "Macro.h"

class GameObject;

enum COMPONENT_TYPE {
	Renderable,
	Light,
	Rigidbody,
	Collider
};

class Component {
public:
	Component(GameObject* g, COMPONENT_TYPE ct);
	virtual ~Component() {}

	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}
	inline hBOOL checkEnabled() const {
		return isEnabled;
	}

public:
	GameObject* parentGmObj;
	COMPONENT_TYPE compType;
	hBOOL isEnabled;
};

#endif