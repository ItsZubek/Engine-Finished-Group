#include "platform/windows/GLFWWindowsSystem.h"

namespace Engine {

	void GLFWWindowsSystem::start(SystemSignal init = SystemSignal::None, ...)
	{
		glfwInit();
	}
	void GLFWWindowsSystem::stop(SystemSignal init = SystemSignal::None, ...)
	{
		glfwTerminate();
	}
}