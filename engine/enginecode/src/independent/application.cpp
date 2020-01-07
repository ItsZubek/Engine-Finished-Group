/** \file application.cpp
*/
#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#endif // NG_PLATFORM_WINDOWS



namespace Engine {
	Application* Application::s_instance = nullptr;


	Application::Application()
	{
#ifdef NG_PLATFORM_WINDOWS
		m_Window = std::unique_ptr<Window>(Window::Create());
#endif //NG_PLATFORM_WINDOWS
		
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

	void Application::onEvent(EventBaseClass& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
	}
	bool Application::onClose(WindowCloseEvent & e)
	{
		ENGINE_CORE_INFO("Closing application");
		m_running = false;
		return true;
	}
	bool Application::onResize(WindowResizeEvent & e)
	{
		ENGINE_CORE_INFO("Resize window to {0} x {1}", e.getWidth(), e.getHeight());
		return true;
	}

	void Application::run()
	{
		
		float accumulatedTime = 0.f;
		ENGINE_CORE_INFO("Logger Initialized");
		mp_timer->SetStartPoint();
		mp_timer->SetFrameStart();



		while (m_running)
		{
			mp_timer->SetFrameEnd();
			mp_timer->FrameCounter();

			fps = 1.0f / mp_timer->FrameCounter();
			mp_timer->SetFrameStart();
	
			ENGINE_CORE_TRACE("FPS: {0}", fps);
			accumulatedTime += fps;
			if (accumulatedTime > 10.f)
			{
				WindowResizeEvent e1(1024, 720);
				onEvent(e1);
				WindowCloseEvent e2;
				onEvent(e2);
			}
			m_Window->onUpdate();
		}
		mp_timer->SetEndPoint();
		TimeElapsedInSeconds = mp_timer->ElapsedTime();
		ENGINE_CORE_WARN("Time Elapsed in Seconds {0}",TimeElapsedInSeconds);	
	}

}
