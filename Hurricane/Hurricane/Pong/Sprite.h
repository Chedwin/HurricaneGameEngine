#pragma once 

#include <glew.h>
#include <Macro.h>
#include <Vertex.h>


class Sprite {
public:
	Sprite();
	~Sprite();

	void Init();
	void Render();

private:
	GLuint _vao;
	GLuint _vboID[2];
	Vertex verData[4];
};