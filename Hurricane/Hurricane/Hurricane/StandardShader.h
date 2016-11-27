//*******************************//
//
// Name:			StandardShader.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 26, 2016
// Last updated:	Nov 26, 2016
//
//*******************************//


#ifndef STANDARD_SHADER_H
#define STANDARD_SHADER_H

#include <glew.h>
#include "Macro.h"
#include "ShaderProgram.h"

#define STANDARD_SHADER StandardShader::GetInstance();

class StandardShader : public ShaderProgram {
protected:
	StandardShader();
	~StandardShader();
public:
	static StandardShader* GetInstance();

protected:
	static StandardShader*_stndShader;
public:
	GLuint view_Location, projection_Location, model_Location;
	GLuint rotation_Location;
};

#endif