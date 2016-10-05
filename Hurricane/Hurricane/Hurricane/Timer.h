//*******************************//
//
// Name:			Timer.h
// Description:		A basic description of the header goes here.
//
// Author:			Author Name
// Created:			Sep 12, 2016
// Last updated:	Sep 13, 2016
//
//*******************************//

#pragma once

#ifndef TIMER_H
#define TIMER_H

#include "Macro.h"
#include "Clock.h"

class Timer {
public:
	Timer();
	~Timer() {}

	void Start();
	void Pause();

	void UpdateTimer();
	void ResetTimer();

	hFLOAT MillisecondsPassed();
	hFLOAT SecondsPassed();

	inline void SetScale(hDOUBLE sc) {
		scaleFactor = sc;
	}

	inline hDOUBLE GetScale() const {
		return scaleFactor;
	}

	inline hUINT GetTimerTicks() const {
		return (hUINT)ticks.QuadPart;
	}

private:
	bool paused;
	hLARGE_INT start_time;
	hLARGE_INT ticks;
	hLARGE_INT pause_time;
	hDOUBLE scaleFactor;
};

#endif