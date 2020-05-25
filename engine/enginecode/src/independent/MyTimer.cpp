/** \file MyTimer.cpp
*/
#include "engine_pch.h"
#include "systems/MyTimer.h"

namespace Engine {

	void MyTimer::start(SystemSignal init, ...)
	{
		startClock = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::stop(SystemSignal init, ...)
	{
		endClock = std::chrono::high_resolution_clock::now();
	}

	float MyTimer::getFrameTimeSecomds()
	{
		endClock = std::chrono::high_resolution_clock::now();
		timePassed = endClock - startClock;
		startClock = std::chrono::high_resolution_clock::now();

		return timePassed.count();
	}

	void MyTimer::RestartClock()
	{
		startClock = std::chrono::high_resolution_clock::now();
	}
	
	 
}