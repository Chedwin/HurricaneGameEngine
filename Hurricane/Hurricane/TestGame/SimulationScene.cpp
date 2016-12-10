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

	MODEL_MANAGER->LoadAssimpModel("Player", "models/LeafsFan.fbx");
	MODEL_MANAGER->LoadAssimpModel("Puck", "models/Puck.obj");
	TEXTURE_MANAGER->UploadTextureFromFile("PuckTexture", "textures/Puck.png");
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

	GameObject* sun = new GameObject(this, "Sun");
	MeshComponent* planet = new MeshComponent(sun, stdShader, "Player");

	sun->Translate(VEC3(0.0, -0.8, 0.0));
	sun->Scale(VEC3(0.02, 0.02, 0.02));
}

void SimulationScene::Update(const hFLOAT _timeStep)
{
	// Call the base class' update first
	Scene::Update(_timeStep);


}	
