#include "FPSCounter.h"

UNIQUE_PTR(FPSCounter) FPSCounter::_fpsInstance(nullptr); // Declare static unique pointer


FPSCounter * FPSCounter::GetFPSCounter()
{
	if (_fpsInstance.get() == nullptr) {
		_fpsInstance.reset(new FPSCounter());
	}
	return _fpsInstance.get();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void FPSCounter::CalculateFPS() 
{
	// TODO
}