/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "imgui.h"
#include "systems/MyTimer.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Profiler
{
private:
	const char* m_Name;
	bool m_Stopped;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
public:
	Profiler(const char* name)
		: m_Name(name), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		std::cout << "Duration: " << (end - start) << duration << std::endl; 
	};
	~Profiler()
	{
		if (m_Stopped == false)
		{
			Stop();
		}
	}
};

engineApp::engineApp()
{
}

engineApp::~engineApp()
{

}



Engine::Application* Engine::startApplication()
{
	Profiler profile("Engine::Application* Engine::startApplication");
	return new engineApp();
}