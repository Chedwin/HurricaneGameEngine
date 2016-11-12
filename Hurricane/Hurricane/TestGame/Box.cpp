#include <Debug.h>
#include <ShaderProgramManager.h>
#include <Vertex.h>
#include "Box.h"

GLfloat vertices[] = {
	//// front
	//-1.0, -1.0,  1.0,
	//1.0, -1.0,  1.0,
	//1.0,  1.0,  1.0,
	//-1.0,  1.0,  1.0,
	//// back
	//-1.0, -1.0, -1.0,
	//1.0, -1.0, -1.0,
	//1.0,  1.0, -1.0,
	//-1.0,  1.0, -1.0,

	-1.0, -1.0, 0.0,
	0.0, 1.0, 0.0,
	1.0, -1.0, 0.0
};

GLfloat color[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	//1.0, 1.0, 1.0,
	//// back colors
	//1.0, 0.0, 0.0,
	//0.0, 1.0, 0.0,
	//0.0, 0.0, 1.0,
	//1.0, 1.0, 1.0,
};



Box::Box() : GameObject()
{
	//ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	//ShaderProgram* program = SHADER_MANAGER->GetShaderProgram(i);

	Vertex v[3];

	v[0].SetPosition(-1.0f, -1.0f, 0.0f);
	v[1].SetPosition(0.0f, 1.0f, 0.0f);
	v[2].SetPosition(1.0f, -1.0f, 0.0f);

	for (int i = 0; i < 3; i++) {
		v[i].SetColour(0, 255, 0, 1);
	}



	glGenBuffers(1, buffers);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

Box::~Box() 
{
	glDeleteBuffers(2, buffers);
}

GLint NumVertices = 3;

void Box::Render() 
{
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}