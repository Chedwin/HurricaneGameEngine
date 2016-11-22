#pragma once

#include <glew.h>
#include <Macro.h>
#include <Game.h>
#include <ShaderProgram.h>
#include <Camera.h>

class TestGame : public Game {
public:
	TestGame();
	~TestGame();

	hBOOL InitGame() override;

	void GameUpdate(const hFLOAT _deltaTime) override;
	void GameRender() override;

public:
};