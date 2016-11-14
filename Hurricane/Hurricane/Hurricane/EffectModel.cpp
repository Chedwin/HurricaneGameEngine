#include "EffectModel.h"

EffectModel::EffectModel() 
{
	matEffect = nullptr;
	matEffect = new MaterialEffect(this, "Effected Material");
}

EffectModel::~EffectModel()
{
	delete matEffect;
	matEffect = nullptr;
}




void EffectModel::Render()
{
}