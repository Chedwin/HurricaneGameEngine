//*******************************//
//
// Name:			ModelManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Oct 17, 2016
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
	ModelManager();
	~ModelManager();

	static ModelManager* GetModelManager();

	ResourceHandle<Model> LoadModel(STRING& _name, Model* _model);
	void DeleteModel(STRING& _model);

	ResourceHandle<Model> GetModelHandle(STRING& _name);
	Model* GetModel(ResourceHandle<Model>& _handle);

private:
	static UNIQUE_PTR(ModelManager) _modelManager;
	friend DEFAULT_DELETE(ModelManager);

protected:
	ResourceManager<Model> _modelResources;

};

#endif