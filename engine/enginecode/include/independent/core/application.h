/** \file application.h
*/
#pragma once


#include "systems/MyLogger.h"
#include "systems/MyTimer.h"
#include "windows/window.h"
#include "windows/OrthographicCamera.h"
#include <Box2D/Box2D.h>

#include "events/KeyEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

#include <glm/glm.hpp>

#include "Physics/PlayerShape.h"





namespace Engine {

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides ...
	*/

	class Application
	{
	protected:
		Application(); //!< Constructor
	private:
		static Application* s_instance; //!< Singleton instance of the application
		std::shared_ptr<MyLogger> mp_logger; //!< Shared Pointer to a logger
		std::shared_ptr<MyTimer> mp_timer; //!< Shared Pointer to a timer
		float TimeElapsedInSeconds; //!< Time Elapsed in seconds
		float fps; //!< Frames Per Second
		bool onWindowClose(WindowCloseEvent& e); //!< On Window Close Event
		bool onResize(WindowResizeEvent& e); //!< On Window Resize Event
		bool onKeyPress(KeyPressedEvent& e); //!< On Key Pressed Event
		bool onKeyRelease(KeyReleasedEvent& e); //!< On Key Released Event
		bool onMouseButtonPress(MouseButtonPressedEvent& e); //!< On Mouse Button Pressed Event
		bool onMouseButtonRelease(MouseButtonReleasedEvent& e); //!< On Mouse Button Released Event
		bool onMouseScroll(MouseScrolledEvent& e); //!< Mouse Scrolled Event
		bool onMouseMoved(MouseMovedEvent& e); //!< Mouse Moved Event
		bool m_running = true; //!< Bool to keep the application running
		std::unique_ptr<Window> m_Window; //!< Pointer to a window class
		static glm::ivec2 s_screenResolution; //!< Screen resolution
		static float s_timestep; //!< last frame timestep

		std::shared_ptr<Shader> m_ShaderFC; //!< Pointer to a shader class
		std::shared_ptr<Shader> m_ShaderTP; //!< Pointer to a shader class

		std::shared_ptr<VertexArray> m_VertexArrayFC; //!< Pointer to a Vertex Array Class
		std::shared_ptr<VertexArray> m_VertexArrayTP; //!< Pointer to a Vertex Array Class

		std::shared_ptr<VertexBuffer> m_VertexBufferFC; //!< Pointer to a Vertex Buffer class
		std::shared_ptr<VertexBuffer> m_VertexBufferTP; //!< Pointer to a Vertex Buffer class

		std::shared_ptr<IndexBuffer> m_IndexBufferFC; //!< Pointer to a Index Buffer class
		std::shared_ptr<IndexBuffer> m_IndexBufferTP; //!< Pointer to a Index Buffer class

		OrthographicCamera m_Camera; //!< Orthographic Camera

		// Used For Assimp
		/*std::shared_ptr<aiScene> m_ModelScene;
		std::shared_ptr<aiMesh> m_ModelMesh;
		std::shared_ptr<aiNode> m_ModelNode;
		*/
		std::shared_ptr<Texture> m_TextureTP;

		b2World* boxWorld = nullptr;
		b2Vec2 m_gravity = b2Vec2(0.f, 0.f);

		const int m_iVelIterations = 7;
		const int m_iPosIterations = 5;

		
		
		


//Code provided by SIMON COUPLAND
#pragma region TempVars
		// Temp stuff
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?

		//glm::mat4 FCtranslation = glm::mat4(1.0f);
		std::array<bool, 4> m_FCdirection = { false, false, false, false };
#pragma endregion TempVars

		float TimeElapsedInSeconds; //!< Time Elapsed in seconds
		float fps; //!< Frames Per Second
		 //!< Pointer to a window class
		static glm::ivec2 s_screenResolution; //!< Screen resolution

	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(EventBaseClass& e); //!< Called when an event happens
		inline Window& GetWindow() { return *m_Window; } //!< Window Getter
		inline static float getTimestep() { return s_timestep; } //!< TimeStep Getter

		bool onWindowClose(WindowCloseEvent& e); //!< On Window Close Event
		bool onResize(WindowResizeEvent& e); //!< On Window Resize Event
		bool onKeyPress(KeyPressedEvent& e); //!< On Key Pressed Event
		bool onKeyRelease(KeyReleasedEvent& e); //!< On Key Released Event
		bool onMouseButtonPress(MouseButtonPressedEvent& e); //!< On Mouse Button Pressed Event
		bool onMouseButtonRelease(MouseButtonReleasedEvent& e); //!< On Mouse Button Released Event
		bool onMouseScroll(MouseScrolledEvent& e); //!< Mouse Scrolled Event
		bool onMouseMoved(MouseMovedEvent& e); //!< Mouse Moved Event
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}