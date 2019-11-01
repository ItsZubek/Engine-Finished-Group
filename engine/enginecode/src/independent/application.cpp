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
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		mp_timer = std::make_shared<MyTimer>();
		mp_timer->start();


	}

	Application::~Application()
	{
		mp_logger->stop();
		mp_logger.reset();
		mp_timer->stop();
	}

	

	void Application::run()
	{
		
		float accumulatedTime = 0.f;
		ENGINE_CORE_INFO("Logger Initialized");
		mp_timer->SetStartPoint();
		mp_timer->SetFrameStart();


		bool run = true;
		while (run)
		{
			mp_timer->SetFrameEnd();
			mp_timer->FrameCounter();

			fps = 1.0f / mp_timer->FrameCounter();
			mp_timer->SetFrameStart();
	
			ENGINE_CORE_TRACE("FPS: {0}", fps);

		}

		mp_timer->SetEndPoint();
		TimeElapsedInSeconds = mp_timer->ElapsedTime();
		ENGINE_CORE_WARN("Time Elapsed in Seconds {0}",TimeElapsedInSeconds);


	
	}

	void Application::onEvent(EventBaseClass& e)
	{
		//Check the event type
		if (e.getEventType() == EventType::WindowResize)
		{
			//cast the event
			WindowResizeEvent re = (WindowResizeEvent&)e;
			//deal with the event
			ENGINE_CORE_INFO("Window resize event. Width {0}. Height {1}", re.getWidth(), re.getHeight());
		}
	}

}
