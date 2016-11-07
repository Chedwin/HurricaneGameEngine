#include "Material.h"

Material::Material()
	: ambient(Color::WHITE), diffuse(Color::WHITE), specular(Color::WHITE), emissive(Color::WHITE), 
	isShaderAttached(false)
{
	// EMPTY
}