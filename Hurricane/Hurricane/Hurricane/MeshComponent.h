//*******************************//
//
// Name:			MeshComponent.h
// Description:		A "renderable" component that carries a mesh or model to be rendered.
//					Similar to Unity "MeshRenderer"
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 20, 2016
//
//*******************************//


#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Debug.h"
#include "Macro.h"
#include "Component.h"
#include "ShaderProgramManager.h"
#include "ModelManager.h"

class MeshComponent : public Component {
public:
	MeshComponent(GameObject* g, ShaderProgram* _shader);
	~MeshComponent();

	void Render();

	Model* GetModel(const STRING& _name);
	Model* GetModel(ResourceHandle<Model>& _handle);

public:
	ShaderProgram* shader;
	Model* mesh;
	STRING meshName;
};

#endif