#include "ModelManager.h"

UNIQUE_PTR(ModelManager) ModelManager::_modelManager(nullptr); // Declare static unique pointer

ModelManager* ModelManager::GetModelManager()
{
	if (_modelManager.get() == nullptr) {
		_modelManager.reset(new ModelManager());
	}
	return _modelManager.get();
}

ModelManager::ModelManager()
{
	// EMPTY
}

ModelManager::~ModelManager()
{
	// EMPTY
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ResourceHandle<Model> ModelManager::LoadModel(STRING& _name, Model* _model)
{
	ResourceHandle<Model> result(-1);

	// Check if the resource name is already in use
	result = _modelResources.Get(_name);
	if (!result.IsNull()) {
		// throw exception
	}

	result = _modelResources.Add(_name, _model);
	return result;
}

void ModelManager::DeleteModel(STRING & _name)
{
	_modelResources.Remove(_name); 
}

ResourceHandle<Model> ModelManager::GetModelHandle(STRING & _name)
{
	return _modelResources.Get(_name);
}

Model * ModelManager::GetModel(ResourceHandle<Model>& _handle)
{
	return _modelResources.Get(_handle);
}

