#include "engine_pch.h"
#include "platform/windows/WindowsWindow.h"

namespace Engine {

	static bool s_GLFWInitialized = false;
	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		init(properties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::init(const WindowProperties& properties)
	{
		m_Data.Title = properties.m_title;
		m_Data.Width = properties.m_width;
		m_Data.Height = properties.m_height;

		ENGINE_CORE_INFO("Creating window {0}, {1}, {2}", properties.m_title, properties.m_width, properties.m_height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			//ENGINE_CORE_ASSERT(success,"Could not initialize GLFW!");
			s_GLFWInitialized = true;

		}
		m_Window = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	void WindowsWindow::setVSync(bool enabled)
	{
		if (enabled)
		
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
	}
	bool WindowsWindow::isVSync() const
	{
		return m_Data.VSync;
	}
	void WindowsWindow::onResize(unsigned int width, unsigned int height)
	{

	}

}