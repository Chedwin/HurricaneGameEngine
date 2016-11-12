#include "MaterialEffect.h"
#include "MaterialManager.h"
#include "ShaderProgramManager.h"
#include "ResourceManager.h"
#include "Debug.h"

MaterialEffect::MaterialEffect(Model* _model, const STRING& _matName)
	: _effectedModel(_model), _materialName(_matName)
{
	// EMPTY
}

MaterialEffect::~MaterialEffect()
{
	// EMPTY
}


/////////////////////////////////////////////////////////////////////////////////////////////////////

void MaterialEffect::ApplyEffect(AbstractRenderer & renderer)
{
	ResourceHandle<Material> handle = MATERIAL_MANAGER->GetMaterialHandle(_materialName);
	Material* material = MATERIAL_MANAGER->GetMaterial(handle);

	STRING shadName = material->GetShaderName();

	if (shadName.length() == 0) {
		Debug::ConsoleError("Shader for material does not exist", __FILE__, __LINE__);
		Debug::Log(EMessageType::ERR, "MaterialEffect", "ApplyEffect", __TIMESTAMP__, __FILE__, __LINE__, "Shader for material does not exist");
		return;
	}

	ResourceHandle<ShaderProgram> shaderHandle = SHADER_MANAGER->GetShaderProgHandle(shadName);

	if (shaderHandle.IsNull())
	{
		Debug::ConsoleError("Shader handle NULL", __FILE__, __LINE__);
		Debug::Log(EMessageType::ERR, "MaterialEffect", "ApplyEffect", __TIMESTAMP__, __FILE__, __LINE__, "Shader handle NULL");
		return;
	}

	ShaderProgram* shaderPgm = SHADER_MANAGER->GetShaderProgram(shaderHandle);
	if (!shaderPgm) 
	{
		Debug::ConsoleError("Shader program can not be found", __FILE__, __LINE__);
		Debug::Log(EMessageType::ERR, "MaterialEffect", "ApplyEffect", __TIMESTAMP__, __FILE__, __LINE__, "Shader program cannot be found");
		return;
	}
	
	glUseProgram(shaderPgm->GetProgramID());
}

void MaterialEffect::PostEffect(AbstractRenderer & renderer)
{
	// EMPTY
}
