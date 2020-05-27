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

#include "imgui.h"
#include "platform/GLFW/Imgui_plat_GLFW.h"



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
		
		
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		mp_timer = std::make_shared<MyTimer>();
		mp_timer->start();
		m_layerStack.reset(new LayerStack());

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		boxWorld = new b2World(m_gravity);

		//!< Sets the position, size, orientation and colour of the player
		m_Player = std::make_shared<Engine::PlayerShape>(boxWorld, glm::vec2(0.0f, -2.5f), glm::vec2(1.f, 0.2f), 0, glm::vec3(0.8f, 0.2f, 0.2f));

		//!< Sets the position, size, orientation and colour of the enemies
		m_Enemies.resize(4);
		m_Enemies[0] = std::make_shared<Engine::EnemyShape>(boxWorld, glm::vec2(2.5f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[1] = std::make_shared<Engine::EnemyShape>(boxWorld, glm::vec2(1.f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[2] = std::make_shared<Engine::EnemyShape>(boxWorld, glm::vec2(-1.f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[3] = std::make_shared<Engine::EnemyShape>(boxWorld, glm::vec2(-2.5f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));

		//!< Sets the position, size, orientation and colour of the bullets

		m_Bullet = std::make_shared<Engine::BulletShape>(boxWorld, glm::vec2(-5.0f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));

		m_Player->setUserData(new std::pair<std::string, void*>(typeid(decltype(m_Player)).name(), &m_Player));
		m_Bullet->setUserData(new std::pair<std::string, void*>(typeid(decltype(m_Bullet)).name(), &m_Bullet));
		for (std::shared_ptr<Engine::EnemyShape>& enemies : m_Enemies) enemies->setUserData(new std::pair<std::string, void*>(typeid(decltype(enemies)).name(), &enemies));


		boxWorld->SetContactListener(&m_CollisionListener); // sets contact listener

		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));
	


		m_audiosystem.Start();
		m_audiosystem.LoadSound("assets/audio/movie_1.mp3");
		m_audiosystem.PlaySounds("assets/audio/movie_1.mp3", glm::vec3(0,0,0), m_audiosystem.VolumeTodB(1.0f));

		mp_imgui = std::shared_ptr<Imgui>(ImguiGLFW::initialise());


		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		mp_imgui->gen(m_Window);


	}
	void Application::run()
	{
		

		mp_imgui->createFrames();

		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);

		ImGui::Begin("GUI Test");
		ImGui::Text("This is a test box");
		ImGui::End();


		while (m_running)
		{
			s_timestep = mp_timer->getFrameTimeSecomds();

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (auto it = m_layerStack->begin(); it != m_layerStack->end(); it++)
			{
				(*it)->OnUpdate(s_timestep);
			}

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			boxWorld->Step(s_timestep, m_iVelIterations, m_iPosIterations);

			m_Player->update();
			m_Player->draw(projection, view); // draws the player to the screen

			m_Bullet->update();
			m_Bullet->draw(projection, view);

			for (int i = 0; i < 4; i++)
			{
				m_Enemies[i]->update();
				m_Enemies[i]->draw(projection, view); // draws the enemies to the screen
			}
			
			m_audiosystem.Update();

			mp_imgui->render();

			m_Window->onUpdate();
			

		}
		mp_imgui->close();
	}

	Application::~Application()
	{
		mp_logger->stop();
		mp_logger.reset();
		mp_timer->stop();
		m_audiosystem.Stop();

		delete boxWorld;
		boxWorld = nullptr;
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
		if (e.GetKeyCode() == 65) m_Player->movement(b2Vec2(0.2, 0.0f));
		if (e.GetKeyCode() == 68) m_Player->movement(b2Vec2(-0.2f, 0.0f));
		if (e.GetKeyCode() == 32)
		{
			b2Vec2 playerPos = m_Player->playerPosition();
			m_Bullet->setPosition(b2Vec2(playerPos.x, playerPos.y + 0.2));
			m_Bullet->fire(b2Vec2(0.0f, 0.2f));
		}
		ENGINE_CORE_TRACE("KeyPressed: {0}, RepeatCount: {1}", e.GetKeyCode(), e.GetRepeatCount());
		return true;
	}
	bool Application::onKeyRelease(KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == 65) m_Player->playerStopped();
		if (e.GetKeyCode() == 68) m_Player->playerStopped();
		if (e.GetKeyCode() == 32) m_Bullet->Fired();
		if (e.GetKeyCode() == 83) 
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
