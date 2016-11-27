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
	MODEL_MANAGER->LoadModel("Puck", "models/Puck.obj");
	MODEL_MANAGER->LoadModel("HockeyStick", "models/HockeyStick.obj");
	MODEL_MANAGER->LoadModel("Cube", "models/cube.obj");
	MODEL_MANAGER->LoadModel("LeafsFanCivilian", "models/LeafsFanCivilian.fbx");

	TEXTURE_MANAGER->UploadTextureFromFile("textures/HockeyStick.png", "HockeyStick");
}

SimulationScene::~SimulationScene()
{
}

void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulator!");


	GameObject* sun = new GameObject(this, "sun");
	LightComponent* lit = new LightComponent(sun);
	GameObject* earth = new GameObject(this, "earth");
	earth->transform.position = VEC3(-10.f, -19.0f, -4.5f);
	sun->AddChild(earth);


	ModelManager* mm = MODEL_MANAGER;
	Model* p = mm->GetModel("Puck");
	Model* hs = mm->GetModel("HockeyStick");
	Model* cb = mm->GetModel("Cube");


	ShaderProgram* stdShader = SHADER_MANAGER->GetShaderProgram("StandardShader");

	GameObject* stick = new GameObject(this, "MyHStick");
	MeshComponent* stickMesh = new MeshComponent(stick, stdShader);

	stickMesh->GetModel("HockeyStick");
	stickMesh->GetTexture("HockeyStick");


	GameObject* physicsTest = new GameObject(this, "PhysicsTestObject");
	RigidbodyComponent* rb = new RigidbodyComponent(physicsTest);
	rb->SetEnabled(true);

	GameObject* root = _rootNode.get();

	GameObject* puckClone = Scene::FindGameObject("MyPuck");

	HelloWorldScript* helloworld = new HelloWorldScript("Hello World");
	PlayerMovementScript* playerMove = new PlayerMovementScript("Player Movement");

	GameObject* jimmy = new GameObject(this, "Jimmy");

	jimmy->AttachScript(helloworld);
	jimmy->AttachScript(playerMove);
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);
}
