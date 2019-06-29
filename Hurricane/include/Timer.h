#ifndef TIMER_H
#define TIMER_H

#include "PCH.h"

namespace Hurricane
{

	class Timer {
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTime, m_CurrentTime, m_PreviousTime;
		std::chrono::duration<float> m_TotalDuration;

		float m_DeltaTime;
		bool m_Stopped;
	
	public:
		Timer();
		~Timer();
	
		void Reset();

		void Start();
		void Stop();

		void Pause();
		void Resume();

		void Tick();

		inline constexpr float GetTotalDuration() const 
		{
			return m_TotalDuration.count();
		}

		// in second
		inline float GetDeltaTime() const
		{
			return m_DeltaTime;
		}
	};

}

#endif