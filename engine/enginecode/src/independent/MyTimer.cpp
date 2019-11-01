#include "engine_pch.h"
#include "systems/MyTimer.h"

namespace Engine {

	void MyTimer::SetStartPoint()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::SetEndPoint()
	{
		end = std::chrono::high_resolution_clock::now();
	}
	float MyTimer::TimeElapsed()
	{
		timePassed = end - start;
		seconds = timePassed.count();
		return seconds;
	}

}