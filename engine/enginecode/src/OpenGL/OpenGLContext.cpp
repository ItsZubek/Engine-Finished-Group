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

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback([](GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam) {
			ENGINE_CORE_INFO("OpenGL Debug [type {0}] [severity {1}]; {2}", type, severity, message);
		}, 0);
	}
	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}