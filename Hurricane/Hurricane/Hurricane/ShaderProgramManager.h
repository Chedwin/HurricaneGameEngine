

//*******************************//
//Shader
// Name:			ShaderProgramManager.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 14, 2016
// Last updated:	Oct 14, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include "ResourceManager.h"
#include "ShaderProgram.h"

#ifndef SHADER_PROGRAM_MANAGER_H
#define SHADER_PROGRAM_MANAGER_H

#define SHADER_MANAGER ShaderProgramManager::GetShaderManager()


class ShaderProgramManager {
protected:
	ShaderProgramManager() {}
	~ShaderProgramManager();

public:
	static ShaderProgramManager* GetShaderManager();

	ResourceHandle<ShaderProgram> StoreShaderProg(STRING& _name, ShaderProgram* _sp);

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