//*******************************//
//
// Name:			RenderableComponent.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//


#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H
#include "Debug.h"
#include "Macro.h"
#include "Component.h"

class RenderableComponent : public Component {
public:
	RenderableComponent(GameObject* g);
	~RenderableComponent();

	void Render();
};

#endif