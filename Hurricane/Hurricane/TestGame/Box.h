#pragma once

#include <glew.h>
#include <Macro.h>
#include <GameObject.h>
#include <Texture.h>

class Box : public GameObject {
public:
	Box();
	~Box();

	void Render() override;

	GLuint buffers[3];
	Texture* myCubeTexture;
	GLuint texture[1];
};