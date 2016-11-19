#include "RenderableComponent.h"
#include "Debug.h"

RenderableComponent::RenderableComponent(GameObject* g)
	: Component(g, COMPONENT_TYPE::Renderable)
{
	SetEnabled(true);
}

RenderableComponent::~RenderableComponent()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RenderableComponent::Render()
{
	
}