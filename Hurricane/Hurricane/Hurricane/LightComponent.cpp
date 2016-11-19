#include "LightComponent.h"

//LightComponent::LightComponent(GameObject * _g, Colour _intensity,	LIGHT_TYPE _type, hFLOAT _coneAngle) : Component(_g, COMPONENT_TYPE::Light)
//{
//	colourIntensity = _intensity;
//	LightComponentType = _type;
//	coneAngle = _coneAngle;
//}

LightComponent::LightComponent(GameObject * _g) : Component(_g, COMPONENT_TYPE::Light)
{

}

LightComponent::~LightComponent()
{
	// EMPTY
}

void LightComponent::PushLight()
{
	// TODO: Allow for LightComponent to shine in scene
}
