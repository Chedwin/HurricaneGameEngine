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
	MODEL_MANAGER->LoadOBJ("HockeyStick", "models/hockeystick.obj");

	MODEL_MANAGER->LoadOBJ("Puck", "models/Puck.obj");
	MODEL_MANAGER->LoadAssimpModel("Planet", "models/planet.obj");
	MODEL_MANAGER->LoadOBJ("Planet2", "models/planet.obj");
	MODEL_MANAGER->LoadOBJ("Player", "models/player.obj");

	TEXTURE_MANAGER->UploadTextureFromFile("textures/Puck.png", "PuckTexture");
}

SimulationScene::~SimulationScene()
{
	// EMPTY
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////


void SimulationScene::InitScene()
{
	Debug::ConsoleLog("Welcome to the Hurricane Solar System Simulator!");


	ShaderProgram* stdShader = STANDARD_SHADER;

	//planet->transform.position = ORIGIN;
	//planet->Scale(VEC3(0.5f, 0.5f, 0.5f));

	//GameObject* hockeyStick = new GameObject(this, "Puck");
	//MeshComponent* hsMesh = new MeshComponent(hockeyStick, stdShader, "HockeyStick");
	//hockeyStick->Scale(VEC3(0.3f, 0.3f, 0.3f));


	//GameObject* puck = new GameObject(this, "Sun");
	//MeshComponent* puckMesh = new MeshComponent(puck, stdShader, "Puck");
	//puck->Scale(VEC3(0.3f, 0.3f, 0.3f));
	//puck->Translate(VEC3(2.0f, 2.0f, 2.0f));

	//hockeyStick->AddChild(puck);

	GameObject* player = new GameObject(this, "Player");
	MeshComponent* playerMesh = new MeshComponent(player, stdShader, "Player");

	player->Scale(VEC3(0.02, 0.02, 0.02));
	player->Translate(VEC3(0, -1, 0));
	mainCamera->AddChild(player);
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);
}	
