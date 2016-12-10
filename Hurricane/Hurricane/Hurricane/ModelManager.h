//*******************************//
//
// Name:			ModelManager.h
// Description:		Loads and manages several types of models ranging in different formats (i.e. fbx, obj)
//					Makes use of Assimp (Asset Importer) to retrieve vertices, faces, uvs, etc. from models
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Dec 09, 2016
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

	// Using Assimp
	void LoadAssimpModel(const STRING& _name, const STRING& _filePath); 

	// Homemade OBJ reader
	//hBOOL LoadOBJ(const STRING& _name, const STRING& _filePath);


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