#include <cstddef>
#include <HMath.h>
#include <ShaderProgramManager.h>
#include "Sprite.h"

Sprite::Sprite() {
	Init();
}

Sprite::~Sprite() {
	if (_vboID != 0) { 
		glDeleteBuffers(2, _vboID);
	}
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteVertexArrays(1, &_vao);
}

void Sprite::Init() 
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(2, _vboID);

	//verData[0].pos = { -0.5f, -0.5f, 0.0f };
	//verData[1].pos = { -0.5f, 0.5f, 0.0f };
	//verData[2].pos = { 0.5f, 0.5f, 0.0f };
	//verData[3].pos = { 0.5f, -0.5f, 0.0f };

	//verData[0].col = { 255, 0, 0, 1 };
	//verData[1].col = { 0, 255, 255, 1 };
	//verData[2].col = { 255, 255, 0, 1 };

	GLfloat vertices[4][2] = {
		{ -0.90, -0.90 }, // Square
		{ 0.9, -0.9 },
		{ 0.90, 0.9 },
		{ -0.9, 0.9 }
	};

	GLfloat colorData[4][3] = {
		{ 1, 0, 0 }, // color for vertices
		{ 0, 1, 0 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	};

	//glBindBuffer(GL_ARRAY_BUFFER, _vboID[0]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verData), verData, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));


	//glBindBuffer(GL_ARRAY_BUFFER, _vboID[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verData), verData, GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, col));

	ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	GLuint mod = SHADER_MANAGER->GetShaderProgram(i)->GetProgramID();

	glBindBuffer(GL_ARRAY_BUFFER, _vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindAttribLocation(mod, 0, "vertexPosition");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_DYNAMIC_DRAW);
	glBindAttribLocation(mod, 1, "vertexColor");
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
}

void Sprite::Render() {

	ResourceHandle<ShaderProgram> i = SHADER_MANAGER->GetShaderProgHandle("myShaderProgram").GetIndex();
	GLuint mod = SHADER_MANAGER->GetShaderProgram(i)->GetUniformLocation("model_matrix");

	MATRIX4 model_view;
	glUniformMatrix3fv(mod, 1, GL_FALSE, &model_view[0][0]);


	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.5, 0.0f, 0.0f);
	//glVertex3f(0.5, 0.5f, 0.0f);
	//glEnd();
}