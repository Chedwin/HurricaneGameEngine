//*******************************//
//
// Name:			FPSCounter.h
// Description:		Calculate the current frames per second of the game;
//
// Author:			Edwin Chen
// Created:			Nov 11, 2016
// Last updated:	Nov 11, 2016
//
//*******************************//


#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include "Macro.h"

class FPSCounter {
protected:
	FPSCounter() {}
	~FPSCounter() {}
public:
	static FPSCounter* GetFPSCounter();

	void CalculateFPS();

protected:
	static UNIQUE_PTR(FPSCounter) _fpsInstance;
	friend DEFAULT_DELETE(FPSCounter);
};

#endif