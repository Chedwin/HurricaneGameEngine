//*******************************//
//
// Name:			MaterialEffect.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//


#ifndef MATERIAL_EFFECT_H
#define MATERIAL_EFFECT_H

#include "Macro.h"
#include "Model.h"


class MaterialEffect {
public:
	MaterialEffect(Model* _model, const STRING& _matName);
	~MaterialEffect();

	void ApplyEffect();
	void PostEffect();

	STRING GetMaterialName() const {
		return _materialName;
	}

protected:
	Model* _effectedModel;
	STRING _materialName;
};

#endif