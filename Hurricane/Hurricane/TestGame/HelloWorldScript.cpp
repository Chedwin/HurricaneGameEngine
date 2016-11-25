#include "HelloWorldScript.h"
#include <Debug.h>
#include <GameObject.h>
#include <InputHandler.h>

HelloWorldScript::HelloWorldScript(const STRING & name)
	: GameObjectScript(name)
{
	Debug::ConsoleLog("I'm script and I'm ALIVE!");
}


hBOOL HelloWorldScript::UpdateScript(GameObject* gameObject, const hFLOAT _timeStep)
{
	//MyScriptFunction();

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

void HelloWorldScript::MyScriptFunction()
{
	Debug::ConsoleLog("updating script");
}
