#include "SceneGraph.h"

SceneGraph::SceneGraph() : rootNode(nullptr)
{
	Initialze();
}

SceneGraph::~SceneGraph() 
{
	Destroy();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Initialze()
{
	sceneMap = new MAP(STRING, GameObject*);
	rootNode = new GameObject();
	rootNode->SetName("RootNode");
	MAP(STRING, GameObject*)::iterator iter = sceneMap->begin();
	sceneMap->insert(iter, PAIR(STRING, GameObject*)(rootNode->GetName(), rootNode));
}

void SceneGraph::AddSceneNode(GameObject* node)
{
	MAP(STRING, GameObject*)::iterator iter = sceneMap->begin();
	hINT rListSize = sceneMap->size(); // should start at 0
	rootNode->AddChild(node);
	sceneMap->insert(iter, PAIR(STRING, GameObject*)(node->GetName(), node));
}

void SceneGraph::UpdateSceneNode(const hFLOAT _deltaTime)
{
	MAP(STRING, GameObject*)::iterator iter = sceneMap->begin();
	for (iter = sceneMap->begin(); iter != sceneMap->end(); iter++)
	{
		auto node = iter->second;
		node->Update(_deltaTime);
	}
}

// Render each game object
void SceneGraph::RenderSceneNode()
{
	MAP(STRING, GameObject*)::iterator iter = sceneMap->begin();
	for (iter = sceneMap->begin(); iter != sceneMap->end(); iter++) 
	{
		auto node = iter->second;
		node->Render();
	}
}

void SceneGraph::Destroy()
{
	MAP(STRING, GameObject*)::iterator iter = sceneMap->begin();

	if (sceneMap->size() > 0)
	{
		for (iter = sceneMap->begin(); iter != sceneMap->end(); iter++)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
	sceneMap->clear();
}