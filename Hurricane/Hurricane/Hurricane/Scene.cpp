#include "Scene.h"

Scene::Scene()
{
	// Set up root node
	_rootNode.reset(nullptr);
	//_rootNode = new GameObject("RootNode");

	_rootNode.reset(new GameObject("RootNode"));

	// Make sure the root node is at the origin
	_rootNode->transform.position = ORIGIN;

	// Create the default scene camera
	mainCamera = currentCamera = nullptr;
	mainCamera = new Camera();
	mainCamera->SetName("MainCamera");
	SetCamera(mainCamera);

	AddSceneNode(mainCamera);
}

Scene::~Scene()
{
	ClearAllSceneNodes();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CAMERA
void Scene::SetCamera(Camera* _c) 
{
	currentCamera = _c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SCENE GRAPH

// Add node
void Scene::AddSceneNode(GameObject * g)
{
	if (g != _rootNode.get()) 
	{
		if (g->GetName() == "") 
		{
			STRING newName = "GameObject(" + TO_STRING(GetSceneSize()) + ")";
			g->SetName(newName);
		}
		_rootNode->AddChild(g);	
	}
}

// Remove node
void Scene::RemoveSceneNode(const STRING& gName)
{
	_rootNode->RemoveChild(gName);
}

// Clear all nodes
void Scene::ClearAllSceneNodes() 
{
	_rootNode->ClearAllChildren();
}

GameObject* Scene::FindSceneNode(const STRING& name)
{
	return _rootNode->GetChild(name);
}

GameObject * Scene::FindSceneNode(GameObject * g)
{
	return _rootNode->GetChild(g);
}