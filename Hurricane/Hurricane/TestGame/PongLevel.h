//*******************************//
//
// Name:			PongLevel.h
// Description:		A basic description of the header goes here.
//
// Author:			Edwin Chen
// Created:			Oct 24, 2016
// Last updated:	Oct 24, 2016
//
//*******************************//

#pragma once

#include <Macro.h>
#include <Level.h>

#ifndef PONG_LEVEL_H
#define PONG_LEVEL_H

class PongLevel : public Level 
{
public:
	PongLevel();
	~PongLevel();

	hBOOL InitLevel();
};

#endif