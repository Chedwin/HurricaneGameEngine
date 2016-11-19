#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject * g, COMPONENT_TYPE ct) : compType(ct)
{
	if (g) 
	{
		parentGmObj = g;
		g->AddComponent(this);
	}
	SetEnabled(true);
}