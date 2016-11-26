#include "PlayerMovementScript.h"
#include <InputHandler.h>
#include <GameObject.h>
#include <Debug.h>

PlayerMovementScript::PlayerMovementScript(const STRING & name)
	: GameObjectScript(name)
{

}

hBOOL PlayerMovementScript::UpdateScript(GameObject * gameObject, const hFLOAT _timeStep)
{
	if (INPUT->IsKeyDown(SDLK_a)) {
		gameObject->Translate(VEC3(0.01f, 0.044f, 0.3f));
		COUT << "Move with A: ";
		Debug::ConsoleLog(gameObject->transform.position);
	}
	else if (INPUT->IsKeyDown(SDLK_d)) {
		gameObject->Translate(VEC3(-0.91f, -0.01f, 0.8892f));
		COUT << "D movement: ";
		Debug::ConsoleLog(gameObject->transform.position);
	}

	return true;
}
