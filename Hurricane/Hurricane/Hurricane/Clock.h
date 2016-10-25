//*******************************//
//
// Name:			Clock.h
// Description:		Used to calculate real time within a game.
//
// Author:			Edwin Chen
// Created:			Sep 12, 2016
// Last updated:	Sep 13, 2016
//
//*******************************//

#pragma once

#include "Macro.h"

#ifndef CLOCK_H
#define CLOCK_H

class Clock {
public:

	static void init();

	static inline hFLOAT elapsedTimeSeconds()
	{
		return ticksInSeconds(getCurrentTicks());
	}

	static inline hFLOAT elapsedTimeMiliseconds()
	{
		return ticksToMiliseconds(getCurrentTicks());
	}

	static inline LARGE_INTEGER getHardwareTickSpeed() {
		hLARGE_INT speed;
		QueryPerformanceCounter(&speed);
		return speed;
	}

private:
	Clock() {}
	~Clock() {}

	static hLARGE_INT _ticksPerSecond;
	static hLARGE_INT _hardwareSpeed;
	static hLARGE_INT _startTime;


	static inline hFLOAT ticksInSeconds(hLARGE_INT _ticks) {
		return ((hFLOAT)_ticks.QuadPart) / ((hFLOAT)_ticksPerSecond.QuadPart);
	}

	static inline hFLOAT ticksToMiliseconds(hLARGE_INT _ticks) {
		return ticksInSeconds(_ticks) * 1000.0f;
	}

	static inline hLARGE_INT getCurrentTicks() {
		hLARGE_INT v;
		v.QuadPart = getHardwareTickSpeed().QuadPart;
		return v;
	}


};

#endif