//*******************************//
//
// Name:			SceneGraph.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 17, 2016
//
//*******************************//


#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Macro.h"
#include "HMath.h"
#include "GameObject.h"

class SceneGraph {
public:
	SceneGraph(); // TODO: design and implement scene graph
	~SceneGraph();

	void Initialze();
	void AddSceneNode(GameObject* node);
	void UpdateSceneNode(const hFLOAT _deltaTime);
	void RenderSceneNode();
	void Destroy();

public:
	GameObject* rootNode;
	MAP(STRING, GameObject*)* sceneMap;
};

#endif