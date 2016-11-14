//*******************************//
//
// Name:			EffectModel.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//

#ifndef EFFECT_MODEL_H
#define EFFECT_MODEL_H

#include "Macro.h"
#include "Model.h"
#include "MaterialEffect.h"

class EffectModel : public Model {
public:
	EffectModel();
	~EffectModel();

	void Render();

public:
	MaterialEffect* matEffect;
};

#endif
