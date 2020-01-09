/** \file application.cpp
*/
#include "engine_pch.h"
#include "core/application.h"
#include "systems/Input.h"

#ifdef NG_PLATFORM_WINDOWS
#endif // NG_PLATFORM_WINDOWS



namespace Engine {
	Application* Application::s_instance = nullptr;


	Application::Application()
	{
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		mp_timer = std::make_shared<MyTimer>();
		mp_timer->start();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		if (s_instance == nullptr)
		{
			s_instance = this;
		}


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
		dispatcher.dispatch<WindowCloseEvent>(std::bind(&Application::onWindowClose, this, std::placeholders::_1));
		dispatcher.dispatch<WindowResizeEvent>(std::bind(&Application::onResize, this, std::placeholders::_1));
		dispatcher.dispatch<KeyPressedEvent>(std::bind(&Application::onKeyPress, this, std::placeholders::_1));
		dispatcher.dispatch<KeyReleasedEvent>(std::bind(&Application::onKeyRelease, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&Application::onMouseButtonPress, this, std::placeholders::_1));
		dispatcher.dispatch<MouseButtonReleasedEvent>(std::bind(&Application::onMouseButtonRelease, this, std::placeholders::_1));
		dispatcher.dispatch<MouseScrolledEvent>(std::bind(&Application::onMouseScroll, this, std::placeholders::_1));
		dispatcher.dispatch<MouseMovedEvent>(std::bind(&Application::onMouseMoved, this, std::placeholders::_1));
	}
	bool Application::onWindowClose(WindowCloseEvent & e)
	{
		ENGINE_CORE_TRACE("Closing application");
		m_running = false;
		return true;
	}
	bool Application::onResize(WindowResizeEvent & e)
	{
		ENGINE_CORE_TRACE("Resize window to {0} x {1}", e.getWidth(), e.getHeight());
		return true;
	}

	bool Application::onKeyPress(KeyPressedEvent& e)
	{
		ENGINE_CORE_TRACE("KeyPressed: {0}, RepeatCount: {1}", e.GetKeyCode(), e.GetRepeatCount());
		return true;
	}
	bool Application::onKeyRelease(KeyReleasedEvent& e)
	{
		ENGINE_CORE_TRACE("KeyReleased: {0}", e.GetKeyCode());
		return true;
	}
	bool Application::onMouseButtonPress(MouseButtonPressedEvent& e)
	{
		ENGINE_CORE_TRACE("MouseButtonPressed: {0}", e.GetMouseButton());
		return true;
	}

	bool Application::onMouseButtonRelease(MouseButtonReleasedEvent& e)
	{
		ENGINE_CORE_TRACE("MouseButtonReleased: {0}", e.GetMouseButton());
		return true;
	}
	bool Application::onMouseScroll(MouseScrolledEvent& e)
	{
		ENGINE_CORE_TRACE("MouseScrolled: X: {0}, Y: {1}", e.GetXOffset(), e.GetYOffset());
		return true;
	}
	bool Application::onMouseMoved(MouseMovedEvent& e)
	{
		ENGINE_CORE_TRACE("MouseMoved: {0}, {1}", e.GetX(), e.GetY());
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
			/*mp_timer->SetFrameEnd();
			mp_timer->FrameCounter();

			fps = 1.0f / mp_timer->FrameCounter();
			mp_timer->SetFrameStart();
	
			ENGINE_CORE_TRACE("FPS: {0}", fps);
			accumulatedTime += fps;
			if (accumulatedTime > 10.f)
			
				WindowResizeEvent e1(1024, 720);
				onEvent(e1);
				WindowCloseEvent e2;
				onEvent(e2);
			}*/

			auto x = Input::GetMouseX();
			auto y = Input::GetMouseY();

			//ENGINE_CORE_TRACE("{0}, {1}", x, y );

			m_Window->onUpdate();


		}
		//mp_timer->SetEndPoint();
		//TimeElapsedInSeconds = mp_timer->ElapsedTime();
		//ENGINE_CORE_WARN("Time Elapsed in Seconds {0}",TimeElapsedInSeconds);	
	}

}
