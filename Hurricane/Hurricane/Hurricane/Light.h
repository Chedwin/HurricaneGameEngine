//*******************************//
//
// Name:			Light.h
// Description:		
//
// Author:			Author Name
// Created:			Jan 01, 2016
// Last updated:	Jan 01, 2016
//
//*******************************//


#ifndef CLASS_NAME_H
#define CLASS_NAME_H

#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"
#include "Component.h"
#include "Colour.h"

class Light : public Component {
public:
	enum Light_Type {
		Point,
		Spot,
		Directional
	};

	Light(GameObject* _g, Colour _intensity, Light_Type _type, hFLOAT _coneAngle);
	~Light();

	void PushLight();

public:
	hFLOAT coneAngle;
	Light_Type lightType;
	Colour colourIntensity;
};


#endif