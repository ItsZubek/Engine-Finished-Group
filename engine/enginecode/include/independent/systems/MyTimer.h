#pragma once
#include <chrono>
namespace Engine {

	class MyTimer
	{
	private:
		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point end;
		std::chrono::duration<float> timePassed;
		float seconds;

	public:
		MyTimer() {};
		void SetStartPoint();
		void SetEndPoint();
		float TimeElapsed();
	};
}