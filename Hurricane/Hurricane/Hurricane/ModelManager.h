//*******************************//
//
// Name:			ModelManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Oct 03, 2016
//
//*******************************//

#pragma once

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "Macro.h"
#include "ResourceManager.h"
#include "Model.h"

#define MODEL_MANAGER ModelManager::GetModelManager();

class ModelManager 
{
public:
	typedef ResourceHandle<Model> HandleType;

	ModelManager();
	~ModelManager();

	static ModelManager* GetModelManager();

private:
	static UNIQUE_PTR(ModelManager) _modelManager;
	friend DEFAULT_DELETE(ModelManager);

public:
	ResourceManager<Model> modelResources;
};

#endif