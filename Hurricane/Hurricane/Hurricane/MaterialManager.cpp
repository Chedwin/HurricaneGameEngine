#include "MaterialManager.h"

UNIQUE_PTR(MaterialManager) MaterialManager::_materialManager(nullptr);

MaterialManager* MaterialManager::GetMaterialManager() {
	if (_materialManager.get() == nullptr) {
		_materialManager.reset(new MaterialManager());
	}
	return _materialManager.get();
}



MaterialManager::~MaterialManager() 
{
	_materialResources.EmptyResourceMap();
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////

ResourceHandle<Material> MaterialManager::StoreMaterial(STRING& _name, Material* _mat)
{
	ResourceHandle<Material> result(-1);
	result = _materialResources.Get(_name);

	if (!result.IsNull()) {
		// throw exception
	}

	result = _materialResources.Add(_name, _mat);
	return result;
}

ResourceHandle<Material> MaterialManager::GetMaterialHandle(const STRING& _name)
{
	return _materialResources.Get(_name);
}

Material * MaterialManager::GetMaterial(ResourceHandle<Material>& _handle)
{
	return _materialResources.Get(_handle);
}

void MaterialManager::DeleteMaterial(STRING & _name)
{
	_materialResources.Remove(_name);
}