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
	AudioManager m_audiosystem;


#pragma region TempGlobalVars
	
#pragma endregion TempGlobalVars

	Application::Application()
	{
		
		boxWorld = new b2World(m_gravity);
		m_Player = std::make_shared<PlayerShape>();
		
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		ENGINE_CORE_INFO("Logging Initalised");
		mp_timer.reset(new MyTimer());
		mp_timer->start();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));


		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		m_audiosystem.Start();
		m_audiosystem.LoadSound("assets/audio/movie_1.mp3");
		m_audiosystem.PlaySounds("assets/audio/movie_1.mp3", glm::vec3(0, 0, 0), m_audiosystem.VolumeTodB(1.0f));


		m_Window = std::shared_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

		mp_imgui->gen(m_Window);

		mp_timer->ElapsedTime();

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
			m_audiosystem.Update();
			m_Window->onUpdate();
			s_timestep = mp_timer->ElapsedTime();

			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
			{
				(*it)->OnUpdate(s_timestep);
			}
		}
		mp_imgui->close();
	}

			FCtranslation = FCmodel;
			if (m_FCdirection[1]) { FCtranslation = glm::translate(FCmodel, glm::vec3(-0.25f * s_timestep, 0.0f, 0.0f)); }
			if (m_FCdirection[3]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.25f * s_timestep, 0.0f, 0.0f)); }
			if (m_FCdirection[0]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.25f * s_timestep, 0.0f)); }
			if (m_FCdirection[2]) { FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.25f * s_timestep, 0.0f)); }

			m_timeSummed += s_timestep;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}


			FCmodel = glm::rotate(FCtranslation, glm::radians(20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second
			TPmodel = glm::rotate(TPtranslation, glm::radians(-20.f) * s_timestep, glm::vec3(0.f, 1.f, 0.f)); // Spin the cube at 20 degrees per second

			// End of code to make the cube move.

			glm::mat4 fcMVP = projection * view * FCmodel;
			
			//Binds the Shader and Vertex Array for Flat Colour
			m_ShaderFC->Bind();
			m_VertexArrayFC->bind();

			// Uploads the Flat Colour Uniform to the Shader
			m_ShaderFC->UploadUniformMat4("u_MVP", &fcMVP[0][0]);

			glDrawElements(GL_TRIANGLES, m_IndexBufferFC->GetCount(), GL_UNSIGNED_INT, nullptr);

			glm::mat4 tpMVP = projection * view * TPmodel;
			//m_TextureTP->getSlot();
			unsigned int textureSlot;
			if (m_goingUp) m_TextureTP->setSlot(0);
			else  m_TextureTP->setSlot(1);


			//Binds the Shader and Vertex Array for Textured Phong
			m_ShaderTP->Bind();
			m_VertexArrayTP->bind();
			
			
			// Uploads the Textured Phong Uniforms to the Shader

			m_ShaderTP->UploadUniformMat4("u_MVP", &tpMVP[0][0]);

			m_ShaderTP->UploadUniformMat4("u_model", &TPmodel[0][0]);

			m_ShaderTP->uploadFloat3("u_objectColour", 0.2f, 0.8f, 0.5f);

			m_ShaderTP->uploadFloat3("u_lightColour", 1.0f, 1.0f, 1.0f);

			m_ShaderTP->uploadFloat3("u_lightPos", 1.0f, 4.0f, -6.0f);

			m_ShaderTP->uploadFloat3("u_viewPos", 0.0f, 0.0f, -4.5f);

			m_ShaderTP->uploadInt("u_texData", m_TextureTP->getSlot() /*textureSlot*/ );

			glDrawElements(GL_TRIANGLES, m_IndexBufferTP->GetCount() , GL_UNSIGNED_INT, nullptr);
			

			// End temporary code
#pragma endregion TempDrawCode
			
			

			m_Window->onUpdate();
			s_timestep = mp_timer->ElapsedTime();

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
