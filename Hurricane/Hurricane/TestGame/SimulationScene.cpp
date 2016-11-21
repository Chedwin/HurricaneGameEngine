#include "SimulationScene.h"
#include <Debug.h>
#include <ModelManager.h>
#include <GameObject.h>
#include <MeshComponent.h>

SimulationScene::SimulationScene()
{
	SetSceneName("Solar System Simulation");
	MODEL_MANAGER->LoadModel("Puck", "models/Puck.obj");
	MODEL_MANAGER->LoadModel("HockeyStick", "models/HockeyStick.obj");
	MODEL_MANAGER->LoadModel("Cube", "models/cube.obj");
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

	

	ModelManager* mm = MODEL_MANAGER;
	Model* p = mm->GetModel("Puck");
	Model* hs = mm->GetModel("HockeyStick");
	Model* cb = mm->GetModel("Cube");

	ShaderProgram* shader = new ShaderProgram("shader");
	shader->CompileShaders("../shaders/colourShading.vert", "../shaders/colourShading.frag");
	//shader->AddAttribute("vertexPosition");
	//shader->AddAttribute("vertexUV");
	//shader->AddAttribute("vertexNormal");

	SHADER_MANAGER->StoreShaderProg(shader->GetProgramName(), shader);

	GameObject* puck = new GameObject("MyPuck");
	MeshComponent* puckMesh = new MeshComponent(puck, shader);


	AddSceneNode(sun);
	AddSceneNode(puck);

	RemoveSceneNode("earth");


	GameObject* puckClone = Scene::FindSceneNode("MyPuck");
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	if (INPUT->IsKeyDown(SDLK_w)) {
		
	}
	else if (INPUT->IsKeyDown(SDLK_s)) {
		
	}
}
