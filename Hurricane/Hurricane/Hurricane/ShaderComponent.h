//*******************************//
//
// Name:			ShaderComponent.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Oct 12, 2016
//
//*******************************//


#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#pragma once

#include "Macro.h"

class ShaderVariable 
{
public:
	/** This specifies whether a variable is IN, OUT, or INOUT */
	enum VariableAccessType {
		ACCESS_NONE = 0,
		ACCESS_IN,
		ACCESS_OUT,
		ACCESS_INOUT
	};

	/** Specifies whether the variable is Uniform, vertex or varying */
	enum ShaderVariableType {
		SHADER_VAR_NONE = 0,
		SHADER_VAR_UNIFORM,
		SHADER_VAR_ATTRIBUTE,
		SHADER_VAR_VARYING
	};

	ShaderVariable() : accessType(VariableAccessType::ACCESS_NONE), variableType(ShaderVariableType::SHADER_VAR_NONE) {}

private:
	/** The resource name for this shader variable */
	STRING			name;
	/** The name of the variable used within the shader programs */
	STRING			sourceName;
	/** Whether the variable is IN, OUT or INOUT */
	VariableAccessType	accessType;
	/** whether the variable is vertex, uniform or varying */
	ShaderVariableType	variableType;
};



class ShaderComponent
{
public:
	enum ShaderType {
		SHADER_TYPE_NONE = 0,
		SHADER_TYPE_VERTEX,
		SHADER_TYPE_FRAGMENT
	};

private:
	ShaderType	shaderType = ShaderType::SHADER_TYPE_NONE;
	STRING		shaderSource;
};
#endif