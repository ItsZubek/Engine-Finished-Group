#pragma once

#include "imgui.h"
#include "systems/MyTimer.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <chrono>


namespace Engine
{
	struct ProfResult //profiler result struct
	{
		const char* Name;
		float Time;

	};

	std::vector<ProfResult> m_ProfResults; //vector for profiler results

	template<typename Fn>
	class Profiler
	{
	private:
		Fn m_Func;
		const char* m_Name;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;

	public:
		Profiler(const char* name, Fn&& func)
			: m_Name(name), m_Func(func), m_Stopped(false)
		{
			m_StartTimePoint = std::chrono::high_resolution_clock::now();
		}

		void Stop()
		{
			auto endTimePoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

			m_Stopped = true;

			float duration = (end - start) * 0.001f;
			m_Func({ m_Name, duration });
			std::cout << m_Name << ": " << duration << "ms" << std::endl; //need m_Name and duration to be accessible from application.h

		};
		~Profiler()
		{
			if (m_Stopped == false)
			{
				Stop();
			}
		}
	};

}

#define PROFILE_SCOPE(name) Profiler profiler##__LINE__(name, [&](ProfResult ProfResult) { m_ProfResults.push_back(ProfResult); })
