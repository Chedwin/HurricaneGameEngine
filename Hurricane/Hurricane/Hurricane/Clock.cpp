#include "Clock.h"

hLARGE_INT Clock::_hardwareSpeed;
hLARGE_INT Clock::_ticksPerSecond;
hLARGE_INT Clock::_startTime;

void Clock::init()
{
	QueryPerformanceFrequency(&_ticksPerSecond);
	_startTime = getHardwareTickSpeed();
}