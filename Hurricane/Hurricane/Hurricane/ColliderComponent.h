//*******************************//
//
// Name:			Collider.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//


#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "Macro.h"
#include "Component.h"

class ColliderComponent : public Component {
public:
	ColliderComponent(GameObject* g);
	~ColliderComponent();
};

#endif