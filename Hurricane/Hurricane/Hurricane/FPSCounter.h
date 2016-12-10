//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game.
//					Only the class Game can access these functions.
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	Dec 10, 2016
//
//*******************************//


#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include "Macro.h"

#define FPS_COUNTER FPSCounter::GetFPSCounter()

class FPSCounter {
	friend class Game;
protected:
	void CalculateFPS();

	FPSCounter() {}
	~FPSCounter() {}

	static FPSCounter* GetFPSCounter();

	void Init(hFLOAT maxfps);
	void SetMaxFPS(hFLOAT maxfps);

	void BeginFrame();
	hFLOAT End(); // will compute FPS

protected:
	static UNIQUE_PTR(FPSCounter) _fpsInstance;
	friend DEFAULT_DELETE(FPSCounter);

	hFLOAT _maxFPS;
	hUINT  _startTicks;

	hFLOAT _fps;
	hFLOAT _frameTime;
};

#endif