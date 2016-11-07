#include "MaterialEffect.h"
#include "MaterialManager.h"
#include "Debug.h"

MaterialEffect::MaterialEffect()
{
}

MaterialEffect::~MaterialEffect()
{
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

void MaterialEffect::ApplyEffect(AbstractRenderer & renderer)
{
	MATERIAL_MANAGER;
}

void MaterialEffect::PostEffect(AbstractRenderer & renderer)
{
}
