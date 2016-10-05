#include "Timer.h"

Timer::Timer()
{
	ResetTimer();
}



void Timer::Start()
{
	if (!paused)
	{
		start_time.QuadPart = Clock::elapsedTimeMiliseconds();
		ticks = start_time;
	}
	else if (paused)
	{
		start_time.QuadPart = Clock::elapsedTimeMiliseconds() - pause_time.QuadPart;
		paused = false;
	}
}

void Timer::Pause()
{
	if (!paused)
	{
		paused = true;
		pause_time.QuadPart = Clock::elapsedTimeMiliseconds() - start_time.QuadPart;
	}
}

void Timer::UpdateTimer()
{
	if (!paused)
	{
		ticks.QuadPart = Clock::elapsedTimeMiliseconds();
	}
}

void Timer::ResetTimer()
{
	ticks.QuadPart = 0;
	pause_time.QuadPart = 0;
	start_time.QuadPart = 0;
	paused = false;
	scaleFactor = 1.0;
}


hFLOAT Timer::MillisecondsPassed()
{
	return (hFLOAT)ticks.QuadPart - (hFLOAT)start_time.QuadPart;
}

hFLOAT Timer::SecondsPassed()
{
	return MillisecondsPassed() / 1000.0f;
}