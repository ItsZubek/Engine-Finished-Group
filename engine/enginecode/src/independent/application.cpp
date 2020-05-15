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

#pragma region TempSetup
		//  Temporary set up code to be abstracted

		// Enable standard depth detest (Z-buffer)
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		// Enabling backface culling to ensure triangle vertices are correct ordered (CCW)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////Box2D Shapes//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		// Shape the player will control
		m_Player = PlayerShape(boxWorld,b2Vec2(0.5f, 1.f), b2Vec2(1.f,2.f), 0.f);

		// Enemies to attack the player
		m_Enemies.resize(4);
		m_Enemies[0] = EnemyShape(boxWorld, b2Vec2(-1.5, 0), b2Vec2(1, 1), 0.f);
		m_Enemies[1] = EnemyShape(boxWorld, b2Vec2(-1.5, 0), b2Vec2(1, 1), 0.f);
		m_Enemies[2] = EnemyShape(boxWorld, b2Vec2(-1.5, 0), b2Vec2(1, 1), 0.f);
		m_Enemies[3] = EnemyShape(boxWorld, b2Vec2(-1.5, 0), b2Vec2(1, 1), 0.f);

		// Bullets to destroy the eemy
		m_Bullets.resize(10);
		m_Bullets[0] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[1] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[2] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[3] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[4] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[5] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[6] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[7] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[8] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		m_Bullets[9] = BulletShape(boxWorld, b2Vec2(0.5f, 1.f), b2Vec2(0.5, 0.5), 0.f);
		
		

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////Flat Colour Cube//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		// Intiating the Vertex Array
		m_VertexArrayFC.reset(VertexArray::create());

		// Initiating the Vertex Buffer 
		m_VertexBufferFC.reset(VertexBuffer::Create(FCvertices, sizeof(FCvertices)));
		

		// Initiating the Buffer Layout
		BufferLayout FCBufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 } };

		// Adds the Buffer Layout to the Vertex Buffer
		m_VertexBufferFC->setBufferLayout(FCBufferLayout);

		//Sets the Buffer Layout
		m_VertexArrayFC->setVertexBuffer(m_VertexBufferFC);
		
		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};

		

		// Initiating the Index Buffer 
		m_IndexBufferFC.reset(IndexBuffer::Create(indices, 3 * 12));
		m_IndexBufferFC->Bind();
		m_VertexArrayFC->setIndexBuffer(m_IndexBufferFC);
		
		// Initiating the Shader
		m_ShaderFC.reset(Shader::create("assets/shaders/flatColour.glsl"));
		m_ShaderFC->Bind();

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////Textured Phong Cube////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		float TPvertices[8 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.5f,
			 0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
			-0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f, 0.33f, 0.f,
			-0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33f, 0.5f,
			 0.5f, -0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.5f,
			 0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.66f, 0.f,
			-0.5f,  0.5f, 0.5f,  0.f, 0.f, 1.f, 0.33, 0.f,
			-0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 1.f, 0.f,
			 0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f, 0.66f, 0.f,
			 0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 0.66f, 0.5f,
			-0.5f, -0.5f, 0.5f,  0.f, -1.f, 0.f, 1.0f, 0.5f,
			-0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.33f, 1.0f,
			 0.5f, 0.5f, -0.5f,  0.f, 1.f, 0.f, 0.f, 1.0f,
			 0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 0.5f,
			-0.5f, 0.5f, 0.5f,   0.f, 1.f, 0.f, 0.3f, 0.5f,
			-0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f, 0.33f, 0.5f,
			-0.5f,  0.5f, 0.5f,  -1.f, 0.f, 0.f, 0.66f, 0.5f,
			-0.5f,  -0.5f, 0.5f, -1.f, 0.f, 0.f, 0.66f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f, 1.0f, 0.5f,
			0.5f,  0.5f, 0.5f, 1.f, 0.f, 0.f,  0.66f, 0.5f,
			0.5f,  -0.5f, 0.5f,  1.f, 0.f, 0.f, 0.66f, 1.0f
		};

		// Initiating the Vertex Array
		m_VertexArrayTP.reset(VertexArray::create());

		// Iinitiating the Vertex Buffer
		m_VertexBufferTP.reset(VertexBuffer::Create(TPvertices, sizeof(TPvertices)));

		// Initiating the Buffer Layout
		BufferLayout TPBufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 }, {ShaderDataType::Float2} };

		// Adds the Buffer Layout to the Vertex Buffer
		m_VertexBufferTP->setBufferLayout(TPBufferLayout);

		//Sets the Buffer Layout
		m_VertexArrayTP->setVertexBuffer(m_VertexBufferTP);
		
		// Initiating the Index Buffer
		m_IndexBufferTP.reset(IndexBuffer::Create(indices, 3 * 12));
		m_IndexBufferTP->Bind();
		m_VertexArrayTP->setIndexBuffer(m_IndexBufferTP);

		// Initiating the Shader
		m_ShaderTP.reset(Shader::create("assets/shaders/texturedPhong.glsl"));
		m_ShaderTP->Bind();

		// Initiating the Textures
		m_TextureTP.reset(Texture::createFromFile("assets/textures/letterCube.png"));
		m_TextureTP.reset(Texture::createFromFile("assets/textures/numberCube.png"));

		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));

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
			mp_timer->SetStartPoint();
			boxWorld->Step(s_timestep, m_iVelIterations, m_iPosIterations);


#pragma region TempDrawCode
			// Temporary draw code to be abstracted

			glClearColor(0.8f, 0.8f, 0.8f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLoadIdentity();

			// Update the position of the player
			m_Player.update();

			// Update the position of all the bullets
			for (int i = m_Bullets.begin; i < m_Bullets.max_size(); i++)
			{
				m_Bullets[i].update();
			}

			///////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////// Draw Box2D Shape //////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////
			/*b2Body* shapes = boxWorld->GetBodyList();
			//b2Vec2 m_vertices[4];
			while (shapes)
			{
				for (int i = 0; i < 4; i++)
				{
					m_vertices[i] = ((b2PolygonShape*)shapes->GetFixtureList()->GetShape())->GetChildCount();
					m_Player->drawShape(m_vertices, shapes->GetWorldCenter(), shapes->GetAngle());
					b2Fixture shape = 
					
					shapes = shapes->GetNext();
				
				}
				
				
			}
			*/

			//glDrawElements(GL_QUADS, shapes->GetFixtureList()->GetShape()->GetChildCount(), GL_UNSIGNED_INT, nullptr);

			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -4.5f), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;

			if (m_goingUp)
			{
				//FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
			}
			else
			{
				//FCtranslation = glm::translate(FCmodel, glm::vec3(0.0f, -0.2f * s_timestep, 0.0f));
				TPtranslation = glm::translate(TPmodel, glm::vec3(0.0f, 0.2f * s_timestep, 0.0f));
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
		if (e.GetKeyCode() == 65) { m_FCdirection[1] = true; }
		if (e.GetKeyCode() == 68) { m_FCdirection[3] = true; }
		if (e.GetKeyCode() == 87) { m_FCdirection[0] = true; }
		if (e.GetKeyCode() == 83) { m_FCdirection[2] = true; }
		if (e.GetKeyCode() == 65) { m_Player.Movement(b2Vec2(-2.f, 0.f)); }
		if (e.GetKeyCode() == 68) { m_Player.Movement(b2Vec2(2.f, 0.f)); }
		if (e.GetKeyCode() == 32) { m_Bullets[0].Movement(b2Vec2(0.f, 2.f)); }
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
