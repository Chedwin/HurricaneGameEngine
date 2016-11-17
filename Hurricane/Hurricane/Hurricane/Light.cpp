#include "Light.h"

Light::Light(GameObject * _g, Colour _intensity, Light_Type _type, hFLOAT _coneAngle) : Component(_g, COMPONENT_TYPE::Light)
{
	colourIntensity = _intensity;
	lightType = _type;
	coneAngle = _coneAngle;
}

Light::~Light()
{
	// EMPTY
}

void Light::PushLight()
{
}
