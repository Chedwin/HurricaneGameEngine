#include "StandardShader.h"

StandardShader* StandardShader::_stndShader(nullptr);

StandardShader* StandardShader::GetInstance()
{
	if (_stndShader == nullptr) {
		_stndShader = new StandardShader();
	}
	return _stndShader;
}


StandardShader::StandardShader() : ShaderProgram()
{
	_programName = "StandardShader";

	CompileShaders("../shaders/StandardShader.vert", "../shaders/StandardShader.frag");

	glBindAttribLocation(_programID, Attribute_Type::VERTEX_ATTRIBUTE, "vPosition");
	glBindAttribLocation(_programID, Attribute_Type::TEXTURE_ATTRIBUTE, "vTexCoord");
	glBindAttribLocation(_programID, Attribute_Type::NORMAL_ATTRIBUTE, "vNormal");

	_numAttributes = 3;

	LinkShaders();

	model_Location = GetUniformLocation("model_matrix");
	projection_Location = GetUniformLocation("projection_matrix");
	view_Location = GetUniformLocation("view_matrix");

	UseShader();
}

StandardShader::~StandardShader()
{
	UnuseShader();
}