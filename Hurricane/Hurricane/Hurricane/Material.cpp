#include "Material.h"

Material::Material(const STRING& _name) : _isShaderAttached(false)
{
	SetMaterialName(_name);
}