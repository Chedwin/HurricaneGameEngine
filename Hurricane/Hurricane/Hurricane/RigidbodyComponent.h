//*******************************//
//
// Name:			RigidbodyComponent.h
// Description:	
//
// Author:			Edwin Chen
// Created:			Nov 17, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//


#ifndef RIGIDBODY_COMPONENT_H
#define RIGIDBODY_COMPONENT_H

#include "Macro.h"
#include "HMath.h"
#include "Component.h"
#include "ColliderComponent.h"

class RigidbodyComponent : public Component {
protected:
	void InitBody();
public:
	RigidbodyComponent(GameObject* _g);
	~RigidbodyComponent();

	void AddForce(VEC3 _force);

public:
	hFLOAT mass;
	VEC3 centerOfMass;
	VEC3 velocity;
	VEC3 accel;
};


#endif