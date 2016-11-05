#pragma once

#include <glew.h>
#include <Macro.h>
#include <GameObject.h>

class Ball : public GameObject 
{
public: 
	Ball();
	~Ball();

	void Render() override;
};