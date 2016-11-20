#include "Scene.h"

Scene::Scene()
{
	// Set up root node
	rootNode = nullptr;
	rootNode = new GameObject("RootNode");
	// Make sure the root node is at the origin
	rootNode->transform.position = ORIGIN;

	// Create the default scene camera
	mainCamera = currentCamera = nullptr;
	mainCamera = new Camera();
	mainCamera->SetName("MainCamera");
	currentCamera = mainCamera;


	AddSceneNode(rootNode);
	AddSceneNode(mainCamera);
}

Scene::~Scene()
{
	RemoveAllSceneNodes();
	delete rootNode;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SCENE GRAPH

void Scene::AddSceneNode(GameObject * g, const STRING& name)
{
	UNORDERED_MAP(STRING, GameObject*)::iterator iter = sceneGraph.begin();

	// Does a game object with the same name already exist in the scene graph?
	// Also don't let anybody delete the root node
	for (iter = sceneGraph.begin(); iter != sceneGraph.end(); iter++) {
		if (iter->first == g->GetName() || iter->first == name || iter->first == rootNode->GetName()) {
			return;
		}		
	}

	// Is your inserted game object already named? If not, we'll give it one!
	if (g->GetName() != "") {
		sceneGraph.insert(PAIR(STRING, GameObject*)(g->GetName(), g));	
	}
	else {
		hINT size = GetNumSceneNodes();
		STRING goName = "GameObject(" + TO_STRING(size) + ")"; // "GameObject(n)" how many objects there are already 
		sceneGraph.insert(PAIR(STRING, GameObject*)(goName, g));
	}

	// Make sure not to add the root node to itself! 
	if (g != rootNode) {
		rootNode->AddChild(g);	
	}
}

void Scene::RemoveSceneNode(const STRING& gName)
{
	UNORDERED_MAP(STRING, GameObject*)::iterator iter = sceneGraph.begin();

	for (iter = sceneGraph.begin(); iter != sceneGraph.end(); iter++) {
		if (iter->first == gName) {
			delete iter->second;
			sceneGraph.erase(gName);

			rootNode->RemoveChild(iter->second);
			return;
		}
	}
}

void Scene::RemoveAllSceneNodes() 
{
	sceneGraph.clear();
}

GameObject * Scene::GetSceneNode(const STRING& name)
{
	GameObject* temp = sceneGraph[name];
	return temp;
}