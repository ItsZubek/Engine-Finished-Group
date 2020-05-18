#pragma once

#include "systems/MyTimer.h"
#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Engine {

	class profiler{
	public:
		profiler(const char* name);
		void Stop();
	private :
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
	

}