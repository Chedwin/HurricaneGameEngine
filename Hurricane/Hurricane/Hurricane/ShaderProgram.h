//*******************************//
//
// Name:			ShaderProgram.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Sep 30, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//


#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H


#include <glew.h>
#include "Macro.h"
#include "ResourceManager.h"

enum Attribute_Type
{
	VERTEX_ATTRIBUTE  = 0, 
	TEXTURE_ATTRIBUTE = 1, 
	NORMAL_ATTRIBUTE  = 2
};


class ShaderProgram {
private:
	hBOOL CompileShader(const STRING& filePath, GLuint id);
public:
	ShaderProgram(const STRING& _progName="");
	~ShaderProgram();

	hBOOL CompileShaders(const STRING& verPath, const STRING& fragPath);

	void LinkShaders();
	void AddAttribute(const STRING& attrName);
	
	GLint GetUniformLocation(const STRING& uniformName);

	void UseShader();
	void UnuseShader();

	void RemoveFromGPU(GLuint id);

	inline GLuint GetProgramID() const {
		return _programID;
	}

	inline STRING GetProgramName() const {
		return _programName;
	}

private:
	hINT _numAttributes;
	GLuint _programID, _vertexShaderID, _fragmentShaderID;

	STRING _programName;
};

#endif