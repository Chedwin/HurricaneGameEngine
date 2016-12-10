//*******************************//
//
// Name:			MeshComponent.h
// Description:		A "renderable" component that carries a mesh or model to be rendered.
//					Similar to Unity "MeshRenderer"
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Dec 09, 2016
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
	enum Buffer_Type
	{
		VERTEX_BUFFER = 0,
		TEXTURE_BUFFER = 1,
		NORMAL_BUFFER = 2
	};

	MeshComponent(GameObject* g, ShaderProgram* _shader, const STRING& _model);
	~MeshComponent();

	Model* GetModel(const STRING& _name);
	Texture* GetTexture(const STRING& _texture);

	void BindBuffers();

	void Render();

public:
	ShaderProgram* shader;
	Model* mesh;
	Texture* texture;

	GLuint textureHandle;
	GLuint textureSampler;

	STRING meshName;
	STRING textureName;

	GLuint vao;
	GLuint ebo;
	GLuint buffers[2];
	GLuint program;
};

#endif