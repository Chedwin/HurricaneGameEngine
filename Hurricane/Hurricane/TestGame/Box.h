#pragma once

#include <glew.h>
#include <Macro.h>
#include <GameObject.h>

class Box : public GameObject {
public:
	Box();
	~Box();

	void Render() override;

	GLuint buffers[2];
};