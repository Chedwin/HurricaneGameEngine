//*******************************//
//
// Name:			Component.h
// Description:		Defines a basic component class for different component types.
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Sep 30, 2016
//
//*******************************//

#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "Macro.h"

class GameObject;

enum COMPONENT_TYPE {
	None=0,
	Rigidbody,
	Light,
	Particle
};

struct Component {
	Component(GameObject* g, COMPONENT_TYPE ct);
	~Component() {}

	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}

	GameObject* parentGmObj;
	COMPONENT_TYPE compType;
	hBOOL isEnabled;
};

#endif