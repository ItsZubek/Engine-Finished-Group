#pragma once
#include "include/independent/windows/window.h"
#include "include/independent/windows/graphicsContext.h"
#include "systems/system.h"
#include "../glfw/include/GLFW/glfw3.h"

namespace Engine {
	class GLFWWindowsSystem : System
	{
	private:

		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
	};

}
