#include "profiler.h"
#include "engine_pch.h"

namespace Engine {
	profiler::profiler(const char * name):m_Name(name),m_Stopped(false){
		m_StartTimepoint = std::chrono::high_resolution_clock::now();

	}
	void stop() {
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();

	}

}