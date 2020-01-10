/** \file MyTimer.cpp
*/
#include "engine_pch.h"
#include "systems/MyTimer.h"

namespace Engine {


	float MyTimer::ElapsedTime()
	{
		//timePassed = endpoint - startPoint;
		seconds = (std::chrono::high_resolution_clock::now() - startPoint).count() * 0.000000001f;
		return seconds;
	}
	void MyTimer::start(SystemSignal init, ...)
	{
		TimerInitializationStartPoint = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::stop(SystemSignal init, ...)
	{
		TimerInitializationEndPoint = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::SetStartPoint()
	{
		startPoint = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::SetEndPoint()
	{
		endpoint = std::chrono::high_resolution_clock::now();
	}
	float MyTimer::RunTime()
	{
		timePassed = TimerInitializationEndPoint - TimerInitializationStartPoint;
		seconds = timePassed.count();
		return seconds;
	}
	void MyTimer::SetFrameStart()
	{
		FrameStart = std::chrono::high_resolution_clock::now();
	}
	void MyTimer::SetFrameEnd()
	{
		FrameEnd = std::chrono::high_resolution_clock::now();
	}
	float MyTimer::FrameCounter()
	{
		FrameDuration = FrameEnd - FrameStart;
		return FrameDuration.count();
	}
	 
}