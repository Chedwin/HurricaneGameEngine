#pragma once

#include <glew.h>
#include <Macro.h>
#include <Game.h>
#include <ShaderProgram.h>

#include "FPSCamera.h"

class TestGame : public Game {
public:
	TestGame();
	~TestGame();

	hBOOL InitGame() override;

	void GameUpdate(const hFLOAT _deltaTime) override;
	void GameRender() override;

	void GameInput(SDL_Event& _evnt) override;

public:
	ShaderProgram* cubeShader;
	GLuint buffers[2];
	GLuint VertexArrayID;

	GLuint location;
	GLuint view_matrix_location;
	GLuint projection_matrix_location;

	FPSCamera* fpsCam;
};