#pragma once
#include "include/independent/windows/window.h"
#include "include/independent/windows/graphicsContext.h"
#include "systems/system.h"
#include "../glfw/include/GLFW/glfw3.h"

class GLFWWindowsSystem
{
private:
	
	int start(); //glfwInit()
	void Close(); //glfwTerminate()
};


