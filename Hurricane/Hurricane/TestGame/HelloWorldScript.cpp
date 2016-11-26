#include "HelloWorldScript.h"
#include <Debug.h>
#include <GameObject.h>
#include <InputHandler.h>

HelloWorldScript::HelloWorldScript(const STRING & name)
	: GameObjectScript(name)
{
	Debug::ConsoleLog("Hello world!");
}


hBOOL HelloWorldScript::UpdateScript(GameObject* gameObject, const hFLOAT _timeStep)
{
	//MyScriptFunction();

	if (INPUT->IsMouseButtonDown(1)) {
		Debug::ConsoleLog("Left Mouse!");
	}
	else if (INPUT->IsMouseButtonDown(2)) {
		Debug::ConsoleLog("Right mouse!");
	}

	return true;
}

void HelloWorldScript::MyScriptFunction()
{
	Debug::ConsoleLog("updating script");
}
