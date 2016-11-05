#include <ShaderProgramManager.h>
#include "Box.h"

static const GLfloat vertexData[] = {
	// front
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0,
};

static const GLfloat colorData[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Box::Box() 
{
	ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	ShaderProgram* program = SHADER_MANAGER->GetShaderProgram(i);

	glGenBuffers(1, &vertexBuf);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindAttribLocation(program->GetProgramID(), 0, "vertexPosition");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &colorBuf);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuf);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);
	glBindAttribLocation(program->GetProgramID(), 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

Box::~Box() 
{

}

void Box::Render() 
{
	ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	GLuint mod = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("model_matrix");

	MATRIX4 model_view;
	glUniformMatrix4fv(mod, 1, GL_FALSE, &model_view[0][0]);
}