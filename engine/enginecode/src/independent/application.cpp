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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Rendering/RenderCommand.h"

#include "platform/OpenGL/Rendering/OpenGLMaterial.h"

#include "glm/gtc/matrix_transform.hpp"

#pragma endregion TempIncludes




namespace Engine 
{
	Application* Application::s_instance = nullptr;
	float Application::s_timestep = 0.f;
	glm::ivec2 Application::s_screenResolution = glm::ivec2(0, 0);


#pragma region TempGlobalVars
	glm::mat4 FCmodel, TPmodel;
#pragma endregion TempGlobalVars

	Application::Application() : m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
	{
		boxWorld = new b2World(m_gravity);
		
		mp_logger = std::make_shared<MyLogger>();
		mp_logger->start();
		mp_timer = std::make_shared<MyTimer>();
		mp_timer->start();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));
		


		Application::s_screenResolution = glm::ivec2(m_Window->getWidth(), m_Window->getHeight());

		
		//m_Renderer->BeginScene(m_Camera);

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		// Enable standard depth detest (Z-buffer)
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		//!< Sets the position, size, orientation and colour of the player
		m_Player = std::make_shared<PlayerShape>(boxWorld, glm::vec2(0.f, -2.5f), glm::vec2(1.f, 0.2f), 0, glm::vec3(0.8f, 0.2f, 0.2f));

		//!< Sets the position, size, orientation and colour of the enemies
		m_Enemies.resize(4);
		m_Enemies[0] = std::make_shared<EnemyShape>(boxWorld, glm::vec2(2.5f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[1] = std::make_shared<EnemyShape>(boxWorld, glm::vec2(1.f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[2] = std::make_shared<EnemyShape>(boxWorld, glm::vec2(-1.f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));
		m_Enemies[3] = std::make_shared<EnemyShape>(boxWorld, glm::vec2(-2.5f, 1.5f), glm::vec2(0.5, 0.5), 0, glm::vec3(0.2f, 0.8f, 0.2f));

		//!< Sets the position, size, orientation and colour of the bullets
		m_Bullets.resize(10);
		m_Bullets[0] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-1.9f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[1] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-2.1f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[2] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-2.3f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[3] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-2.5f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[4] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-2.7f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[5] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-2.9f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[6] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-3.1f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[7] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-3.3f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[8] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-3.5f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));
		m_Bullets[9] = std::make_shared<BulletShape>(boxWorld, glm::vec2(-3.7f, -2.8f), glm::vec2(0.1, 0.1), 0, glm::vec3(0.2f, 0.2f, 0.8f));

		m_Player->setUserData(new std::pair<std::string, void*>(typeid(decltype(m_Player)).name(), &m_Player));
		for (std::shared_ptr<EnemyShape>& enemies : m_Enemies) enemies->setUserData(new std::pair<std::string, void*>(typeid(decltype(enemies)).name(), &enemies));
		for (std::shared_ptr<BulletShape>& bullets : m_Bullets) bullets->setUserData(new std::pair<std::string, void*>(typeid(decltype(bullets)).name(), &bullets));

		boxWorld->SetContactListener(&m_CollisionListener); // sets contact listener
		
		
		// End temporary code

#pragma endregion TempSetup
		


		if (s_instance == nullptr)
		{
			s_instance = this;
		}


	}
	void Application::run()
	{
		

		float accumulatedTime = 0.f;
		mp_timer->SetStartPoint();
		mp_timer->SetFrameStart();

		

		while (m_running)
		{
			ENGINE_CORE_CRITICAL("Timestep {0}", mp_timer->ElapsedTime());
			mp_timer->SetStartPoint();
			
			boxWorld->Step(s_timestep, m_iPosIterations, m_iVelIterations);

#pragma region TempDrawCode
			// Temporary draw code to be abstracted
			
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//m_Renderer->DrawQuad(glm::vec2(0.5, 0.5) , glm::vec2(1,1), glm::vec4(0.8, 0.2, 0.3, 1));

			
		
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			

			m_Player->update();
			m_Player->draw(projection, view); // draws the player to the screen

			for (int i = 0; i < 4; i++)
			{
				m_Enemies[i]->draw(projection, view); // draws the enemies to the screen
			}

			for (int i = 0; i < 10; i++)
			{
				m_Bullets[i]->update();
				m_Bullets[i]->draw(projection, view);
			}
			
		

			m_Window->onUpdate();
			s_timestep = mp_timer->ElapsedTime();

		}
	}

	Application::~Application()
	{
		mp_logger->stop();
		mp_logger.reset();
		mp_timer->stop();

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
		if (e.GetKeyCode() == 65) m_Player->movement(b2Vec2(0.2f, 0.0f));
		if (e.GetKeyCode() == 68) m_Player->movement(b2Vec2(-0.2f, 0.0f));
		if (e.GetKeyCode() == 32) m_Bullets[4]->fire(b2Vec2(0.0f, 0.2f));
		
		
		ENGINE_CORE_TRACE("KeyPressed: {0}, RepeatCount: {1}", e.GetKeyCode(), e.GetRepeatCount());
		return true;
	}

	bool Application::onKeyRelease(KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == 65) m_Player->playerStopped();
		if (e.GetKeyCode() == 68) m_Player->playerStopped();
		 
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
