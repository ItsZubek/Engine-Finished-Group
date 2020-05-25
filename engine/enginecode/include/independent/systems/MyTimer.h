/** \file MyTimer.h
*/
#pragma once
#include <chrono>
#include "system.h"
#include "systems/MyLogger.h"
namespace Engine {
	/**
\class MyTimer
Responsible for timing all actions happening during runtime
*/
	class MyTimer : public System
	{
	private:
		std::chrono::high_resolution_clock::time_point startClock; // start of time
		std::chrono::high_resolution_clock::time_point endClock; // end of time

		std::chrono::duration<float> timePassed; // frame time in seconds
	public:
		MyTimer() {};
		~MyTimer() {};
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;

		float getFrameTimeSecomds();
		void RestartClock();
	
	};
}