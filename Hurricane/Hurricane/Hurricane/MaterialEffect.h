//*******************************//
//
// Name:			MaterialEffect.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef MATERIAL_EFFECT_H
#define MATERIAL_EFFECT_H

#include "Macro.h"
#include "Model.h"
#include "Effect.h"

class MaterialEffect : public Effect {
public:
	MaterialEffect();
	~MaterialEffect();

	void ApplyEffect(AbstractRenderer &renderer);
	void PostEffect(AbstractRenderer &renderer);

	STRING GetMaterialName() const {
		return _materialName;
	}

protected:
	Model* _effectedModel;
	STRING _materialName;
};

#endif