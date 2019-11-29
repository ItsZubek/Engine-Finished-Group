#pragma once
#include "systems/system.h"
#include "include/independent/windows/window.h"

namespace Engine {
	class WindowsSys : System
	{
		void start(SystemSignal init);
		void stop(SystemSignal close);
	};
}