//*******************************//
//
// Name:			ModelManager.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

// Assimp model loading
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing 

#include "Macro.h"
#include "ResourceManager.h"
#include "Model.h"


#define MODEL_MANAGER ModelManager::GetModelManager();
#define NUMBER_OF_BUFFERS 2


class ModelManager {
public:
	ModelManager();
	~ModelManager();

	static ModelManager* GetModelManager();

	ResourceHandle<Model> LoadModel(const STRING& _name, const STRING& _filePath);
	ResourceHandle<Model> LoadModel(const STRING& _name, Model* _model);

	void DeleteModel(const STRING& _model);

	void ClearAllModels();

	ResourceHandle<Model> GetModelHandle(const STRING& _name);
	Model* GetModel(ResourceHandle<Model>& _handle);

private:
	static UNIQUE_PTR(ModelManager) _modelManager;
	friend DEFAULT_DELETE(ModelManager);

protected:
	ResourceManager<Model> _modelResources;

public:
	GLuint Buffers[NUMBER_OF_BUFFERS];
};

#endif