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

}

ModelManager::~ModelManager()
{

}
