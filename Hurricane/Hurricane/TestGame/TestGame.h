//*******************************//
//
// Name:			TestGame.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Sep 18, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once

#include <Macro.h>
#include <DebugLog.h>
#include <Game.h>
#include <glew.h>

#ifndef TEST_GAME_H
#define TEST_GAME_H


class TestGame : public Game 
{
public:
	TestGame();
	~TestGame();

	hBOOL InitGame() override;

	void GameRender() override;
	void GameUpdate(const hFLOAT _deltatime) override;


	ShaderProgram* _shaderProgram;
	ShaderProgramManager* _shaderManager;
	ImageManager* _imageManager;

	Camera* cam3D;

	GLuint Buffers[2];


	GLuint _viewMatLocation;
	GLuint _projMatLocation;
	GLuint _shaderLocation;
};

#endif
