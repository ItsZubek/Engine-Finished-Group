#pragma once
#include <chrono>
#include "system.h"
#include "systems/MyLogger.h"
namespace Engine {

	class MyTimer : public System
	{
	private:
		std::chrono::high_resolution_clock::time_point TimerInitializationStartPoint;
		std::chrono::high_resolution_clock::time_point TimerInitializationEndPoint;
		std::chrono::high_resolution_clock::time_point startPoint;
		std::chrono::high_resolution_clock::time_point endpoint;
		std::chrono::high_resolution_clock::time_point FrameStart;
		std::chrono::high_resolution_clock::time_point FrameEnd;
		std::chrono::duration<float> timePassed;
		std::chrono::duration<float> FrameDuration;
		float seconds;


	public:
		MyTimer() {};
		~MyTimer() {};
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		void SetStartPoint();
		void SetEndPoint();
		float RunTime();
		float ElapsedTime();
		void SetFrameStart();
		void SetFrameEnd();
		float FrameCounter();
	
	};
}