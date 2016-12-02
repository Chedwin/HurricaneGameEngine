//*******************************//
//
// Name:			ModelManager.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 26, 2016
//
//*******************************//

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <glew.h>

#include "Macro.h"
#include "ResourceManager.h"
#include "Model.h"
#include "ShaderProgram.h"

#define MODEL_MANAGER ModelManager::GetModelManager()


class ModelManager {
private:
	ResourceHandle<Model> InsertModel(const STRING& _name, Model* _model); // Insert model into resource manager

public:

	ModelManager();
	~ModelManager();

	static ModelManager* GetModelManager();

	// Add or "import" a model into the manager using Assimp mapping the correct vertices, texture coords, etc.
	void LoadModel(const STRING& _name, const STRING& _filePath); 

	hBOOL LoadOBJ(const STRING& _name, const STRING& _filePath);

	void DeleteModel(const STRING& _model);
	void ClearAllModels();

	ResourceHandle<Model> GetModelHandle(const STRING& _name);
	Model* GetModel(ResourceHandle<Model>& _handle);
	Model* GetModel(const STRING& _name);


private:
	static UNIQUE_PTR(ModelManager) _modelManager;
	friend DEFAULT_DELETE(ModelManager);

protected:
	ResourceManager<Model> _modelResources;
};

#endif