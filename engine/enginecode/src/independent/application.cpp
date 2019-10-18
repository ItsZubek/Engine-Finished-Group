/** \file application.cpp
*/

#ifdef NG_PLATFORM_WINDOWS
#include "windows/window.h"
#endif // NG_PLATFORM_WINDOWS

#include "engine_pch.h"
#include "core/application.h"


namespace Engine {
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
	}

	Application::~Application()
	{
	}

	

	void Application::run()
	{

	}

}
