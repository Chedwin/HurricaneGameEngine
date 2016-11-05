//*******************************//
//
// Name:			Component.h
// Description:		Defines a basic component class for different component types.
//
// Author:			Edwin Chen, Mathieu Violette, James Sholdice, Nathan Senter
// Created:			Sep 30, 2016
// Last updated:	Nov 01, 2016
//
//*******************************//

#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "Macro.h"
#include "ShaderProgram.h"

class GameObject;

enum COMPONENT_TYPE {
	None=0,
	Rigidbody,
	Light,
	Renderable,
	Collider
};

class Component {
public:
	Component(GameObject* g, COMPONENT_TYPE ct);
	~Component() {}

	inline void SetEnabled(hBOOL _b) {
		isEnabled = _b;
	}

	GameObject* parentGmObj;
	COMPONENT_TYPE compType;
	hBOOL isEnabled;
};

class RenderableComponent : public Component 
{
public:
	RenderableComponent(GameObject* g, ShaderProgram* sp);
	~RenderableComponent();

	void Render();
};

#endif