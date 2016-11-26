#pragma once

#include <Macro.h>
#include <GameObjectScript.h>

// Kind of like MonoBehaviour
class HelloWorldScript : public GameObjectScript {
public:
	explicit HelloWorldScript(const STRING& name);
	~HelloWorldScript() {}

	hBOOL UpdateScript(GameObject* gameObject, const hFLOAT _timeStep) final;
	void MyScriptFunction();
};