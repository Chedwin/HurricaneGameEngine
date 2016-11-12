#pragma once

#include <glew.h>
#include <Macro.h>
#include <Game.h>
#include <ShaderProgram.h>
#include <SdlImage.h>
#include <Camera.h>
#include "Box.h"

class NewGame : public Game {
public:
	NewGame();
	~NewGame();

	hBOOL InitGame() override;

	void GameUpdate(const hFLOAT _deltaTime) override;
	void GameRender() override;

	void GameInput(SDL_Event& _evnt) override;

public:
	ShaderProgram* cubeShader;
	//GLuint buffers[3];

	GLuint location;
	GLuint view_matrix_location;
	GLuint projection_matrix_location;

	Box* box;
	Box* box2;
};