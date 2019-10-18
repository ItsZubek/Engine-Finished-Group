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
		float accumulatedTime = 0.f;
	
	}

	void Application::onEvent(EventBaseClass& e)
	{
		//Check the event type
		if (e.getEventType() == EventType::WindowResize)
		{
			//cast the event
			WindowResizeEvent re = (WindowResizeEvent&)e;
			//deal with the event
			//ENGINE_INFO("Window resize event. Width {0}. Height {1}", re.getWidth(), re.getHeight());
		}
	}

}
