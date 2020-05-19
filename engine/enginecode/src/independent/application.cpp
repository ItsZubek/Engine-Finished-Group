/** \file application.cpp
*/
#include "engine_pch.h"
#include "core/application.h"
#include "systems/Input.h"
#include <glad/glad.h>
#include "systems/AssimpLoader.h"
#include "imgui.h"
#include "platform/GLFW/Imgui_plat_GLFW.h"


//#include "events/KeyEvents.h"


#pragma region TempIncludes
// temp includes



#pragma endregion TempIncludes




namespace Engine 
{
	


	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 0.f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);


#pragma region TempGlobalVars
	
#pragma endregion TempGlobalVars

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

		m_Window = std::shared_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

		m_layerStack.reset(new LayerStack());
		
		boxWorld = new b2World(m_gravity);
		
		mp_imgui = std::shared_ptr<Imgui>(ImguiGLFW::initialise());


		

#pragma region TempSetup
		
		// End temporary code

#pragma endregion TempSetup
		

		mp_imgui->gen(m_Window);

	}
	void Application::run()
	{
	

		float accumulatedTime = 0.f;
		mp_timer->SetStartPoint();
		mp_timer->SetFrameStart();

		mp_imgui->createFrames();

		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

		ImGui::Begin("gui");
		ImGui::Text("test texts");
		ImGui::End();

		while (m_running)
		{
			mp_timer->SetStartPoint();
			
			boxWorld->Step(s_timestep, m_iVelIterations, m_iPosIterations);

			mp_imgui->render();

			m_Window->onUpdate();
			s_timestep = mp_timer->ElapsedTime();

			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
			{
				(*it)->OnUpdate(s_timestep);
			}
		}
		mp_imgui->close();
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

		for (auto it = m_layerStack->end(); it != m_layerStack->begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled()) break;
		}

		
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		ENGINE_CORE_TRACE("Closing application");
		m_running = false;
		return true;
	}
	bool Application::onResize(WindowResizeEvent& e)
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
	
}
