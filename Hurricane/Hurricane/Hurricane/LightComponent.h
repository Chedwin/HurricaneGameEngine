//*******************************//
//
// Name:			LightComponent.h
// Description:		Lightng component that can be added to a game object to provide illumination.
//
// Author:			Edwin Chen
// Created:			Nov 15, 2016
// Last updated:	Nov 18, 2016
//
//*******************************//


#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "Macro.h"
#include "HMath.h"
#include "Component.h"
#include "Colour.h"

class LightComponent : public Component {
public:
	enum LIGHT_TYPE {
		Point,
		Spot,
		Directional
	};

	//LightComponent(GameObject* _g, Colour _intensity, LIGHT_TYPE _type, hFLOAT _coneAngle);
	LightComponent(GameObject* _g);
	~LightComponent();

	void PushLight();

public:
	hFLOAT coneAngle;
	LIGHT_TYPE LightComponentType;
	Colour colourIntensity;
};


#endif