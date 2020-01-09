/** \file OpenGLContext.cpp
*/
#include "engine_pch.h"
#include "platform/OpenGL/OpenGLContext.h"
#include "../glfw/include/GLFW/glfw3.h"
#include <glad/glad.h>


namespace Engine {
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}
	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGINE_CORE_INFO("OpenGLContext Initialized");
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}