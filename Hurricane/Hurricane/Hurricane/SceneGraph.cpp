#include "SceneGraph.h"

SceneGraph::SceneGraph()
{
	Initialze();
}

SceneGraph::~SceneGraph() 
{
	delete rootSceneNode;
	rootSceneNode = nullptr;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Initialze()
{
	rootSceneNode = nullptr;
	rootSceneNode = new SceneNode();
}

void SceneGraph::RenderSceneNode(SceneNode * node)
{
}