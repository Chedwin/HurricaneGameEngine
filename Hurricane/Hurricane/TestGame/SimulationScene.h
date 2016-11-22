#pragma once

#include <Macro.h>
#include <Debug.h>
#include <Scene.h>
#include <GameObject.h>
#include <LightComponent.h>
#include <InputHandler.h>

class SimulationScene : public Scene {
public:
	SimulationScene();
	~SimulationScene();

	void InitScene();
	void Update(const hFLOAT _timeStep) override;
};