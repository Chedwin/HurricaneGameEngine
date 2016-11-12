//*******************************//
//
// Name:			Pong.h
// Description:		Sample Pong or Squash like game that illustrates basic rendering, physics, and time step simulations
//
// Author:			Edwin Chen
// Created:			Oct 24, 2016
// Last updated:	Nov 04, 2016
//
//*******************************//

#pragma once

#include <Macro.h>
#include <Game.h>
#include <InputHandler.h>


#ifndef PONG_H
#define PONG_H

class Pong : public Game {
public:
	Pong();
	~Pong();

	hBOOL InitGame() override;

	void GameRender() override;
	void GameUpdate(const hFLOAT _deltatime) override;
	void GameInput(SDL_Event& _evnt) override;

	void WindowTitleUpdate();


public:
	ShaderProgram* _shaderProgram;
	ShaderProgramManager* _shaderManager;

	Camera* pongCam;

	GLuint Buffers[2];


	GLuint _shaderLocation;
};

#endif