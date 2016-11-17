#include "ShaderProgram.h"
#include "Debug.h"



ShaderProgram::ShaderProgram(const STRING& _progName) 
	: _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0), _programID(0), _programName(_progName)
{
	// EMPTY
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(_programID);
}


hBOOL ShaderProgram::CompileShader(const STRING & filePath, GLuint id)
{
	if (id == 0) {
		Debug::ConsoleError("SHADER " + filePath + " FAILED TO COMPILE", __FILE__, __LINE__);
		return false;
	}

	IFSTREAM shaderFile(filePath);
	if (shaderFile.fail()) {
		Debug::ConsoleError("FAILED TO OPEN: " + filePath, __FILE__, __LINE__);
		return false;
	}

	STRING fileContents;
	STRING line;

	while (GETLINE(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();


	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, NULL);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		glDeleteShader(id);
		VECTOR(char) errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		RemoveFromGPU(id);
		PRINTF("%s\n", &(errorLog[0]));
		Debug::ConsoleError("SHADER " + filePath + " FAILED TO COMPILE", __FILE__, __LINE__);
		return false;
	}

	return true;
}



hBOOL ShaderProgram::CompileShaders(const STRING & verPath, const STRING & fragPath)
{
	if (_programID == 0) {
		_programID = glCreateProgram();
	}

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		Debug::ConsoleError("VERTEX SHADER FAILED TO COMPILE", __FILE__, __LINE__);
		return false;
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		Debug::ConsoleError("FRAGMENT SHADER FAILED TO COMPILE", __FILE__, __LINE__);
		return false;
	}

	hBOOL test = CompileShader(verPath, _vertexShaderID);
	hBOOL test2 = CompileShader(fragPath, _fragmentShaderID);
	return test && test2;
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

		RemoveFromGPU(_vertexShaderID);
		RemoveFromGPU(_fragmentShaderID);

		PRINTF("%s\n", &(errorLog[0]));
		Debug::ConsoleError("SHADERS FAILED TO LINK", __FILE__, __LINE__);

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

GLint ShaderProgram::GetUniformLocation(const STRING& uniformName)
{
	GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
	if (loc == GL_INVALID_INDEX)
	{
		Debug::ConsoleError("Uniform: " + uniformName + ", was not found in shader", __FILE__, __LINE__);
	}
	return loc;
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

void ShaderProgram::RemoveFromGPU(GLuint id)
{
	if (id) {
		glDeleteShader(id);
	}
}
