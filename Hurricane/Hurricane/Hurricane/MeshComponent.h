//*******************************//
//
// Name:			MeshComponent.h
// Description:		A "renderable" component that carries a mesh or model to be rendered.
//					Similar to Unity "MeshRenderer"
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 26, 2016
//
//*******************************//


#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include <glew.h>
#include "Debug.h"
#include "Macro.h"
#include "Component.h"
#include "ShaderProgramManager.h"
#include "ModelManager.h"
#include "Texture.h"

class MeshComponent : public Component {
public:
	MeshComponent(GameObject* g, ShaderProgram* _shader);
	~MeshComponent();

	Model* GetModel(const STRING& _name);
	Texture* GetTexture(const STRING& _texture);

	void PushModel();
	void RemoveModelFromGPU();

	void Render();


public:
	ShaderProgram* shader;
	Model* mesh;
	Texture* texture;

	STRING meshName;
	STRING textureName;

	static const GLuint NUMBER_OF_BUFFERS = 3;
	GLuint Buffers[NUMBER_OF_BUFFERS];

	hBOOL areBuffersInitialized;
};

#endif