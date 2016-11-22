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
	MODEL_MANAGER->LoadModel("LeafsFanCivilian", "models/LeafsFanCivilian.fbx");
}

SimulationScene::~SimulationScene()
{
}

void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulatior!");


	GameObject* sun = new GameObject(this, "sun");
	LightComponent* lit = new LightComponent(sun);
	GameObject* earth = new GameObject(this, "earth");
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

	GameObject* puck = new GameObject(this, "MyPuck");
	MeshComponent* puckMesh = new MeshComponent(puck, shader);
	puckMesh->GetModel("Puck");
	GameObject* jimmy = new GameObject(this);

	RemoveSceneNode("sun");

	GameObject* root = _rootNode.get();

	GameObject* puckClone = Scene::FindGameObject("MyPuck");
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);

	if (INPUT->IsKeyDown(SDLK_w)) {
		
	}
	else if (INPUT->IsKeyDown(SDLK_s)) {
		
	}
}
