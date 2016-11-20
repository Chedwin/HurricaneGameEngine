#include "SimulationScene.h"
#include <Debug.h>

SimulationScene::SimulationScene()
{
	SetSceneName("Solar System Simulation");
}

SimulationScene::~SimulationScene()
{
}

void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulatior!");


	GameObject* sun = new GameObject("sun");
	LightComponent* lit = new LightComponent(sun);
	GameObject* earth = new GameObject("earth");
	earth->transform.position = VEC3(-10.f, -19.0f, -4.5f);
	sun->AddChild(earth);

	sun->Translate(VEC3(122.0, 1.5f, -35.0f));
	Debug::ConsoleLog(earth->transform.position);

	////sceneObjects.push_back(sun);
	//AddSceneNode(sun);

	//GameObject* n = GetSceneNode("RootNode");
	//GameObject* p = GetSceneNode("Honoka");

	//RemoveSceneNode("earth");
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	if (INPUT->IsKeyDown(SDLK_w)) {
		
	}
	else if (INPUT->IsKeyDown(SDLK_s)) {
		
	}
}
