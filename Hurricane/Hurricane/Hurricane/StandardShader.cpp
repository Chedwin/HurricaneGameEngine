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

	CompileShaders("StandardShader.vert", "StandardShader.frag");

	AddAttribute(Attribute_Type::VERTEX_ATTRIBUTE, "vPosition");
	AddAttribute(Attribute_Type::TEXTURE_ATTRIBUTE, "vTexCoord");
	AddAttribute(Attribute_Type::NORMAL_ATTRIBUTE, "vNormal");


	LinkShaders();

	model_Location = GetUniformLocation("model");
	projection_Location = GetUniformLocation("projection");
	view_Location = GetUniformLocation("view");
	//rotation_Location = GetUniformLocation("rotation");

	/*UseShader();*/
}

StandardShader::~StandardShader()
{
	UnuseShader();
}