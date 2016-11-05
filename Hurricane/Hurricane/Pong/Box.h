#pragma once

#include <glew.h>
#include <Macro.h>
#include <HMath.h>

class Box {
public:
	Box();
	~Box();
	
	void Render();

public:
	GLuint vertexBuf, colorBuf;
};