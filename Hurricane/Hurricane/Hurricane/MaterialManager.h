//*******************************//
//
// Name:			MaterialManager.h
// Description:		Resource manager for materials
//
// Author:			Edwin Chen
// Created:			Nov 07, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//

#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <glew.h>
#include "Macro.h"
#include "ResourceManager.h"
#include "Material.h"

#define MATERIAL_MANAGER MaterialManager::GetMaterialManager()


class MaterialManager {
protected:
	MaterialManager() {}
	~MaterialManager();
public:
	static MaterialManager* GetMaterialManager();

	ResourceHandle<Material> StoreMaterial(STRING& _name, Material* _mat);

	ResourceHandle<Material> GetMaterialHandle(const STRING& _name);
	Material* GetMaterial(ResourceHandle<Material>& _handle);
	void DeleteMaterial(STRING& _name);

protected:
	static UNIQUE_PTR(MaterialManager) _materialManager;
	friend DEFAULT_DELETE(MaterialManager);

	ResourceManager<Material> _materialResources;

	
};

#endif