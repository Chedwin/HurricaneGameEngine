//*******************************//
//
// Name:			SceneGraph.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 13, 2016
//
//*******************************//


#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Macro.h"
#include "HMath.h"
#include "SceneNode.h"

class SceneGraph {
public:
	SceneGraph();
	~SceneGraph();

	void Initialze();
	void RenderSceneNode(SceneNode* node);

private:
	SceneNode* rootSceneNode;
};

#endif