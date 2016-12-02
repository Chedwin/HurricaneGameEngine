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
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);

	//GameObject* p = FindGameObject("MyPuck");
	//p->Scale(VEC3(0.0001f, 0.0001f, 0.0001f));
}	
