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

		// Intiating the Vertex Array
		m_VertexArrayFC.reset(VertexArray::create());

		float FCvertices[6 * 4] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,

		};

		// Initiating the Vertex Buffer
		m_VertexBufferFC.reset(VertexBuffer::Create(FCvertices, sizeof(FCvertices)));

		// Initiating the Buffer Layout
		BufferLayout FCBufferLayout = { { ShaderDataType::Float3, ShaderDataType::Float3 } };

		// Adds the Buffer Layout to the Vertex Buffer
		m_VertexBufferFC->setBufferLayout(FCBufferLayout);

		m_VertexArrayFC->setVertexBuffer(m_VertexBufferFC);

		unsigned int indices[4] = { 0,1,2,3 };

		// Initiating the Index Buffer 
		m_IndexBufferFC.reset(IndexBuffer::Create(indices, 4));
		m_IndexBufferFC->Bind();
		m_VertexArrayFC->setIndexBuffer(m_IndexBufferFC);

		// Initiating the Shader
		m_ShaderFC.reset(Shader::create("assets/shaders/flatColour.glsl"));
		m_ShaderFC->Bind();

		
		FCmodel = glm::translate(glm::mat4(1), glm::vec3(1.5, 0, 3));
		//TPmodel = glm::translate(glm::mat4(1), glm::vec3(-1.5, 0, 3));
		
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
			
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//m_Renderer->DrawQuad(glm::vec2(0.5, 0.5) , glm::vec2(1,1), glm::vec4(0.8, 0.2, 0.3, 1));
		
			glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f); // Basic 4:3 camera

			glm::mat4 view = glm::lookAt(
				glm::vec3(0.0f, 0.0f, -14.5), // Camera is at (0.0,0.0,-4.5), in World Space
				glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
				glm::vec3(0.f, 1.f, 0.f)  // Standing straight  up
			);

			// Code to make the cube move, you can ignore this more or less.
			glm::mat4 FCtranslation, TPtranslation;


			FCtranslation = FCmodel;
			TPtranslation = TPmodel;
			
			m_timeSummed += s_timestep;
			if (m_timeSummed > 20.0f) {
				m_timeSummed = 0.f;
				m_goingUp = !m_goingUp;
			}
			glm::mat4 fcMVP = projection * view * FCmodel;

			m_ShaderFC->Bind();
			m_VertexArrayFC->bind();

			m_ShaderFC->UploadUniformMat4("u_MVP", &fcMVP[0][0]);

			//m_ShaderFC->setUniformFloat4("u_Colour", glm::vec4(0.8,0.2,0.3,1.0));

			//glm::mat4 transform = glm::translate(glm::mat4(1.f),glm::vec3(0.5, 0.5, 0.f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.f,1.f,1.f));
			//m_ShaderFC->setUniformMat4("u_Transform", transform);

			
			glDrawElements(GL_QUADS, m_IndexBufferFC->GetCount(), GL_UNSIGNED_INT, nullptr);
		


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
