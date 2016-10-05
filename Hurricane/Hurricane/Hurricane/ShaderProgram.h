//*******************************//
//
// Name:			ShaderProgram.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Sep 30, 2016
//
//*******************************//

#pragma once

#include "Macro.h"
#include <glew.h>

#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class ShaderProgram {
private:
	hBOOL CompileShader(const STRING& filePath, GLuint id);
public:
	ShaderProgram();
	~ShaderProgram();

	hBOOL CompileShaders(const STRING& verPath, const STRING& fragPath);

	void LinkShaders();
	void AddAttribute(const STRING& attrName);

	void UseShader();
	void UnuseShader();

private:
	hINT _numAttributes;
	GLuint _programID, _vertexShaderID, _fragmentShaderID;
};

#endif