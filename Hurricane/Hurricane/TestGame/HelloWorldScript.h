#pragma once

#include <Macro.h>
#include <GameObjectScript.h>

class HelloWorldScript : public GameObjectScript {
public:
	HelloWorldScript(const STRING& name);
	~HelloWorldScript() {}

	hBOOL UpdateScript(GameObject* gameObject, const hFLOAT _timeStep) final;
	void MyScriptFunction();
};