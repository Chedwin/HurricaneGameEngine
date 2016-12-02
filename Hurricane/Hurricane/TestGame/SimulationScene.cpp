#include <Debug.h>
#include <ModelManager.h>
#include <GameObject.h>
#include <RigidbodyComponent.h>
#include <MeshComponent.h>
#include <TextureManager.h>
#include <PhysicsEngine.h>
#include <StandardShader.h>

#include "SimulationScene.h"
#include "HelloWorldScript.h"
#include "PlayerMovementScript.h"

SimulationScene::SimulationScene()
{
	SetSceneName("Solar System Simulation");
	MODEL_MANAGER->LoadOBJ("Planet", "models/planet.obj");

	MODEL_MANAGER->LoadOBJ("Puck", "models/Puck.obj");

	TEXTURE_MANAGER->UploadTextureFromFile("textures/Puck.png", "PuckTex");
}

SimulationScene::~SimulationScene()
{
}

void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulator!");


	ShaderProgram* stdShader = STANDARD_SHADER;

	GameObject* planet = new GameObject(this, "Sun");
	MeshComponent* planetMesh = new MeshComponent(planet, stdShader, "Planet");
	planet->transform.position = ORIGIN;
	planet->Scale(VEC3(2, 2, 2));

	GameObject* planet2 = new GameObject(this, "Puck");
	MeshComponent* planetMesh2 = new MeshComponent(planet2, stdShader, "Planet");
	planet2->Translate(VEC3(4, 4, 0));

	planet->AddChild(planet2);
	planet->Scale(VEC3(3, 3, 3));

	//mainCamera->Translate(VEC3(3, 0, 15));

	//GameObject* j1 = new GameObject(this, "");
	//GameObject* j2 = new GameObject(this, "");
	//GameObject* j3 = new GameObject(this, "");
	//GameObject* j4 = new GameObject(this, "");

	//GameObject* root = _rootNode.get();
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);

	//GameObject* p = FindGameObject("Sun");
	//p->ResetTransform();
	//p->Translate(VEC3(0.01f, 0.0f, 0.01f));
	//p->Rotate(QUATERNION(0.1f, 0.1f, 0.1f, 0.1f));
}	
