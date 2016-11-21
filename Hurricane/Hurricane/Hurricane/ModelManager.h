//*******************************//
//
// Name:			ModelManager.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Oct 03, 2016
// Last updated:	Nov 20, 2016
//
//*******************************//

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H



#include "Macro.h"
#include "ResourceManager.h"
#include "Model.h"


#define MODEL_MANAGER ModelManager::GetModelManager()
#define BUFFER_OFFSET(i) ((void*)(i))

class ModelManager {
private:
	ResourceHandle<Model> InsertModel(const STRING& _name, Model* _model); // Insert model into resource manager

public:
	enum Buffer_Type 
	{
		VERTEX_BUFFER = 0, 
		TEXTURE_BUFFER = 1, 
		NORMAL_BUFFER = 2
	};

	ModelManager();
	~ModelManager();

	static ModelManager* GetModelManager();

	// Add or "import" a model into the manager using Assimp mapping the correct vertixes, texture coords, etc.
	void LoadModel(const STRING& _name, const STRING& _filePath); 

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

public:
	static const GLuint NUMBER_OF_BUFFERS = 3;
	GLuint Buffers[NUMBER_OF_BUFFERS];
};

#endif