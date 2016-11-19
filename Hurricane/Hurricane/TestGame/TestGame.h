#pragma once

#include <glew.h>
#include <Macro.h>
#include <Game.h>
#include <ShaderProgram.h>
#include <Camera.h>
#include "Box.h"

class TestGame : public Game {
public:
	TestGame();
	~TestGame();

	hBOOL InitGame() override;

	void GameUpdate(const hFLOAT _deltaTime) override;
	void GameRender() override;

	void GameInput(SDL_Event& _evnt) override;

public:
	ShaderProgram* modelShader;

	GLuint location;
	GLuint view_matrix_location;
	GLuint projection_matrix_location;

	Box* box;
};