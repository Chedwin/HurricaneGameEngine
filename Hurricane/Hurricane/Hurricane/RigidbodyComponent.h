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

class RigidbodyComponent : public Component {
public:

	RigidbodyComponent(GameObject* _g);
	~RigidbodyComponent();

public:
};


#endif