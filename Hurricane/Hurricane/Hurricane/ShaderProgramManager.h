//*******************************//
//Shader
// Name:			ShaderProgramManager.h
// Description:		Contains all the shaders necessary for a game.
//
// Author:			Edwin Chen
// Created:			Oct 14, 2016
// Last updated:	Dec 01, 2016
//
//*******************************//




#ifndef SHADER_PROGRAM_MANAGER_H
#define SHADER_PROGRAM_MANAGER_H

#include "Macro.h"
#include "ResourceManager.h"
#include "ShaderProgram.h"

#define SHADER_MANAGER ShaderProgramManager::GetShaderManager()


class ShaderProgramManager {
protected:
	ShaderProgramManager() {}
	~ShaderProgramManager();

public:
	static ShaderProgramManager* GetShaderManager();

	ResourceHandle<ShaderProgram> StoreShaderProg(const STRING& _name, ShaderProgram* _sp);

	void DeleteShaderProgram(STRING& _name);

	ResourceHandle<ShaderProgram> GetShaderProgHandle(const STRING& _name);
	ShaderProgram* GetShaderProgram(ResourceHandle<ShaderProgram>& _handle);
	ShaderProgram* GetShaderProgram(const STRING& _name);

protected:
	static UNIQUE_PTR(ShaderProgramManager) _shaderProgManager;
	friend DEFAULT_DELETE(ShaderProgramManager);

	ResourceManager<ShaderProgram> _shaderResources;
};

#endif