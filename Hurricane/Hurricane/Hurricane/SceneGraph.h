//*******************************//
//
// Name:			SceneGraph.h
// Description:		
//
// Author:			Edwin Chen
// Created:			Nov 01, 2016
// Last updated:	Nov 07, 2016
//
//*******************************//


#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include "Macro.h"
#include "HMath.h"
#include "Graph.h"
#include "SceneNode.h"

class SceneGraph 
{
public:
	SceneGraph();
	~SceneGraph();

	void Initialze();

private:
	SceneNode* rootSceneNode;

	Graph<SceneNode> _sceneGraph;
};

#endif