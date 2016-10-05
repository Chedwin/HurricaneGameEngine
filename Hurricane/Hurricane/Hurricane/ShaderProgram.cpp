#include "ShaderProgram.h"
#include "DebugLog.h"



ShaderProgram::ShaderProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{
}

ShaderProgram::~ShaderProgram()
{
}


hBOOL ShaderProgram::CompileShader(const STRING & filePath, GLuint id)
{
	id = glCreateShader(GL_VERTEX_SHADER);
	if (id == 0) {
		LOG->Error("SHADER " + filePath + " FAILED TO COMPILE", __LINE__, __FILE__);
		return false;
	}

	IFSTREAM shaderFile(filePath);
	if (shaderFile.fail()) {
		LOG->Error("FAILED TO OPEN: " + filePath, __LINE__, __FILE__);
		return false;
	}

	STRING fileContents;
	STRING line;

	while (GETLINE(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	const hCHAR* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		VECTOR(hCHAR) errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		PRINTF("%s\n", &(errorLog[0]));
		LOG->Error("SHADER " + filePath + " FAILED TO COMPILE", __LINE__, __FILE__);
		return false;
	}

	return true;
}


hBOOL ShaderProgram::CompileShaders(const STRING & verPath, const STRING & fragPath)
{
	_programID = glCreateProgram();

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		LOG->Error("VERTEX SHADER FAILED TO COMPILE", __LINE__, __FILE__);
		return false;
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		LOG->Error("FRAGMENT SHADER FAILED TO COMPILE", __LINE__, __FILE__);
		return false;
	}

	hBOOL test = CompileShader(verPath, _vertexShaderID) && CompileShader(fragPath, _fragmentShaderID);

	return test;
}

void ShaderProgram::LinkShaders()
{
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;

	glGetProgramiv(_programID, GL_LINK_STATUS, (hINT*)&isLinked);
	
	if (isLinked = GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		VECTOR(hCHAR) errorLog(maxLength);
		glGetShaderInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(_programID);

		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		PRINTF("%s\n", &(errorLog[0]));
		LOG->Error("SHADERS FAILED TO LINK", __LINE__, __FILE__);
		return;
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
}

void ShaderProgram::AddAttribute(const STRING & attrName)
{
	glBindAttribLocation(_programID, _numAttributes, attrName.c_str());
	_numAttributes++;
}

void ShaderProgram::UseShader()
{
	glUseProgram(_programID);

	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::UnuseShader()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}
