#include "FPSCounter.h"
#include <SDL.h>

UNIQUE_PTR(FPSCounter) FPSCounter::_fpsInstance(nullptr); // Declare static unique pointer


FPSCounter * FPSCounter::GetFPSCounter()
{
	if (_fpsInstance.get() == nullptr) {
		_fpsInstance.reset(new FPSCounter());
	}
	return _fpsInstance.get();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FPSCounter::Init(hFLOAT maxfps)
{
	SetMaxFPS(maxfps);
}

void FPSCounter::SetMaxFPS(hFLOAT maxfps)
{
	_maxFPS = maxfps;
}

void FPSCounter::BeginFrame()
{
	_startTicks = SDL_GetTicks();
}

hFLOAT FPSCounter::End()
{
	CalculateFPS();

	hFLOAT frameTicks = SDL_GetTicks() - _startTicks;

	if (1000.0f / _maxFPS > frameTicks)
	{
		//SDL_Delay(1000.0f / _maxFPS - frameTicks);
	}

	return _fps;
}

void FPSCounter::CalculateFPS() 
{
	// TODO
	static const hINT NUM_SAMPLES = 100;
	static hFLOAT frameTimes[NUM_SAMPLES];
	static hINT currentFrame = 0;

	static hFLOAT prevTicks = SDL_GetTicks();
	hFLOAT currTicks = SDL_GetTicks();

	_frameTime = currTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currTicks;

	hINT count;

	currentFrame++;
	if (currentFrame < NUM_SAMPLES)
	{
		count = currentFrame;
	}
	else
	{
		count = NUM_SAMPLES;
	}

	hFLOAT frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0)
	{
		_fps = 1000.0f / frameTimeAverage;
	}
	else
	{
		_fps = _maxFPS;
	}
}