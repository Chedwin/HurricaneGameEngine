#pragma once

#include <Macro.h>
#include <GameObjectScript.h>

class PlayerMovementScript : public GameObjectScript {
public:
	explicit PlayerMovementScript(const STRING& name);
	~PlayerMovementScript() {}

	hBOOL UpdateScript(GameObject* gameObject, const hFLOAT _timeStep) final;
};