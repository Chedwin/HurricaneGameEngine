//*******************************//
//
// Name:			TestGame.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Sep 18, 2016
// Last updated:	Sep 29, 2016
//
//*******************************//

#pragma once

#include <Macro.h>
#include <DebugLog.h>
#include <Game.h>

#ifndef TEST_GAME_H
#define TEST_GAME_H

class TestGame : public Game {
public:
	TestGame();
	~TestGame();

	void GameRender();
	void GameUpdate(const hFLOAT _deltatime);
};

#endif
