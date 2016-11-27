#include <Debug.h>
#include <ModelManager.h>
#include <GameObject.h>
#include <RigidbodyComponent.h>
#include <MeshComponent.h>
#include <TextureManager.h>
#include <PhysicsEngine.h>

#include "SimulationScene.h"
#include "HelloWorldScript.h"
#include "PlayerMovementScript.h"

SimulationScene::SimulationScene()
{
	SetSceneName("Solar System Simulation");
	MODEL_MANAGER->LoadModel("PuckObj", "models/planet.obj");
	//MODEL_MANAGER->LoadModel("LeafsFanCivilian", "models/LeafsFanCivilian.fbx");
	//MODEL_MANAGER->LoadModel("HockeyStick", "models/HockeyStick.obj");

	TEXTURE_MANAGER->UploadTextureFromFile("textures/Puck.png", "PuckTex");

	MODEL_MANAGER->PushModels();

	//mainCamera->transform.position = VEC3(0, 0, 0);
}

SimulationScene::~SimulationScene()
{
}

void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulator!");




	ShaderProgram* stdShader = SHADER_MANAGER->GetShaderProgram("StandardShader");

	GameObject* puck = new GameObject(this, "MyPuck");
	MeshComponent* puckMesh = new MeshComponent(puck, stdShader);
	puckMesh->GetModel("PuckObj");


	//GameObject* stick = new GameObject(this, "Stick");
	//MeshComponent* stickMesh = new MeshComponent(stick, stdShader);
	//stickMesh->GetModel("HockeyStick");
	//stick->transform.position = VEC3(0, 0, 0);


	//puckMesh->GetTexture("PuckTex");



	//HelloWorldScript* helloworld = new HelloWorldScript("Hello World");
	//PlayerMovementScript* playerMove = new PlayerMovementScript("Player Movement");

	//GameObject* jimmy = new GameObject(this, "Jimmy");

	//jimmy->AttachScript(helloworld);
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);
}	
