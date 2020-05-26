/** \file application.cpp
*/
#include "engine_pch.h"
#include "core/application.h"
#include "systems/Input.h"
#include <glad/glad.h>
#include "systems/AssimpLoader.h"
//#include "events/KeyEvents.h"


#pragma region TempIncludes
// temp includes
#include <glad/glad.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#pragma endregion TempIncludes




namespace Engine {
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 0.f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);
	AudioManager m_audiosystem;


#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application(): m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
	{
		
		boxWorld = new b2World(m_gravity);
		m_Player = std::make_shared<PlayerShape>();
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		mp_timer = std::make_shared<MyTimer>();
		mp_timer->start();
		m_layerStack.reset(new LayerStack());

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));


		m_audiosystem.Start();
		m_audiosystem.LoadSound("assets/audio/movie_1.mp3");
		m_audiosystem.PlaySounds("assets/audio/movie_1.mp3", glm::vec3(0,0,0), m_audiosystem.VolumeTodB(1.0f));


		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

#pragma region TempSetup

		
		


		if (s_instance == nullptr)
		{
			s_instance = this;
		}


	}
	void Application::run()
	{
		

		
		mp_timer->SetStartPoint();
		mp_timer->SetFrameStart();



		while (m_running)
		{
			mp_timer->SetStartPoint();
			s_timestep = mp_timer->ElapsedTime();
			boxWorld->Step(s_timestep, m_iVelIterations, m_iPosIterations);

			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
			{
				(*it)->OnUpdate(s_timestep);
			}
			
			m_audiosystem.Update();
			m_Window->onUpdate();
		

		}
	}

	Application::~Application()
	{
		mp_logger->stop();
		mp_logger.reset();
		mp_timer->stop();
		m_audiosystem.Stop();
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

		for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled()) break;
		}

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
		if (e.GetKeyCode() == 256) m_running = false;
		if (e.GetKeyCode() == 65) { m_FCdirection[1] = true; }
		if (e.GetKeyCode() == 68) { m_FCdirection[3] = true; }
		if (e.GetKeyCode() == 87) { m_FCdirection[0] = true; }
		if (e.GetKeyCode() == 83) { m_FCdirection[2] = true; }
		ENGINE_CORE_TRACE("KeyPressed: {0}, RepeatCount: {1}", e.GetKeyCode(), e.GetRepeatCount());
		return true;
	}
	bool Application::onKeyRelease(KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == 65) { m_FCdirection[1] = false; }
		if (e.GetKeyCode() == 68) { m_FCdirection[3] = false; }
		if (e.GetKeyCode() == 87) { m_FCdirection[0] = false; }
		if (e.GetKeyCode() == 83) { m_FCdirection[2] = false; }
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
}
