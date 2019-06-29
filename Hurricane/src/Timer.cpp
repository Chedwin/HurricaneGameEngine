#include "PCH.h"
#include "Macro.h"
#include "Timer.h"

namespace Hurricane 
{
	using namespace std::chrono_literals;

	// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
	constexpr std::chrono::nanoseconds FixedTimestep(16ms);

	Timer::Timer() 
	{
	}

	Timer::~Timer() 
	{	
	}

	void Timer::Reset() 
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
		m_CurrentTime = m_StartTime;
		m_PreviousTime = m_StartTime;

		m_TotalDuration = m_CurrentTime - m_StartTime;
		m_Stopped = true;
	}

	void Timer::Start()
	{
		Reset();
		m_Stopped = false;
	}

	void Timer::Stop()
	{
		if (m_Stopped == false) 
		{
			m_CurrentTime = std::chrono::high_resolution_clock::now();
			m_TotalDuration = m_CurrentTime - m_StartTime;
			m_Stopped = true;
		}
	}

	void Timer::Pause()
	{
		m_Stopped = true;
	}

	void Timer::Resume()
	{
		m_Stopped = false;
	}

	void Timer::Tick()
	{
		if (m_Stopped)
		{
			m_DeltaTime = 0.0f;
			return;
		}

		m_CurrentTime = std::chrono::high_resolution_clock::now();
		m_TotalDuration = m_CurrentTime - m_StartTime;

		std::chrono::duration<float> delta = m_CurrentTime - m_PreviousTime;
		m_DeltaTime = delta.count();

		m_PreviousTime = m_CurrentTime;

		if (m_DeltaTime < 0.0f) 
		{
			m_DeltaTime = 0.0f;
		}
	}

}
