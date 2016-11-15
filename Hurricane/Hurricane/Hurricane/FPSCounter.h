//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game.
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	Nov 14, 2016
//
//*******************************//


#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include "Macro.h"

class FPSCounter {
protected:

	void CalculateFPS();
public:
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