#include "Scene.h"
#include "Debug.h"

Scene::Scene()
{
	// Set up root node
	_rootNode.reset(nullptr);
	//_rootNode = new GameObject("RootNode");

	_rootNode.reset(new GameObject(this, ROOT_NAME));

	// Make sure the root node is at the origin
	_rootNode->transform.position = ORIGIN;

	// Create the default scene camera
	mainCamera = currentCamera = nullptr;
	mainCamera = new Camera(this);
	mainCamera->SetName("MainCamera");
	SetCamera(mainCamera);
}

Scene::~Scene()
{
	ClearAllSceneNodes();

	// NOTE: root node get destroyed HERE when it goes OUT OF SCOPE
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// CAMERA
void Scene::SetCamera(Camera* _c) 
{
	currentCamera = _c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATE

void Scene::Update(const hFLOAT _timeStep)
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = _rootNode->childObjects.begin(); iter != _rootNode->childObjects.end(); iter++)
	{
		GameObject* temp = (*iter);

		if (temp && temp->CheckEnabled()) {
			temp->Update(_timeStep);		
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RENDER
void Scene::Render()
{
	VECTOR(GameObject*)::iterator iter;
	for (iter = _rootNode->childObjects.begin(); iter != _rootNode->childObjects.end(); iter++) 
	{
		GameObject* temp = (*iter);
		if (temp && temp->CheckEnabled()) {
			temp->Render();
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SCENE GRAPH

// Add node
void Scene::AddSceneNode(GameObject * g)
{
	STRING test = g->GetName();
	if (test != ROOT_NAME) 
	{
		if (test == "") 
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

// FIND
// by name
GameObject* Scene::FindGameObject(const STRING& name)
{
	return _rootNode->GetChild(name);
}


// how big is the scene graph?
hINT Scene::GetSceneSize() const {
	hINT total = _rootNode->childObjects.size();
	return total;
}