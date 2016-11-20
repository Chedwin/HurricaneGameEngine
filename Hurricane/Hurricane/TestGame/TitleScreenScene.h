#pragma once

#include <Macro.h>
#include <Scene.h>

class TitleScreenScene : public Scene {
public:
	TitleScreenScene();
	~TitleScreenScene();

	void InitScene();
	void Update(const hFLOAT _timeStep);
	void Render();

public:
	hFLOAT countdownTime;
};