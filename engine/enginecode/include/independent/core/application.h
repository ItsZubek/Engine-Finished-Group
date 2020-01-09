/** \file application.h
*/
#pragma once

#include "../events/WindowEvents.h"
#include "../events/KeyEvents.h"
#include "../events/MouseEvents.h"
#include "systems/MyLogger.h"
#include "systems/MyTimer.h"
#include "windows/window.h"
#include <glm/glm.hpp>

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
		std::shared_ptr<MyLogger> mp_logger;
		std::shared_ptr<MyTimer> mp_timer;
		float TimeElapsedInSeconds;
		float fps;
		bool onWindowClose(WindowCloseEvent& e);
		bool onResize(WindowResizeEvent& e);
		bool onKeyPress(KeyPressedEvent& e);
		bool onKeyRelease(KeyReleasedEvent& e);
		bool onMouseButtonPress(MouseButtonPressedEvent& e);
		bool onMouseButtonRelease(MouseButtonReleasedEvent& e);
		bool onMouseScroll(MouseScrolledEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		bool m_running = true;
		std::unique_ptr<Window> m_Window;
		static glm::ivec2 s_screenResolution; //!< Screen res
		static float s_timestep; //!< last frame timestep

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;


#pragma region TempVars
		// Temp stuff
		unsigned int m_FCvertexArray; // Flat Colour VAO
		unsigned int m_FCvertexBuffer;// Flat Colour VBO
		unsigned int m_TPvertexArray; // Textured Phong VAO
		unsigned int m_TPvertexBuffer;// Textured Phong VBO
		unsigned int m_FCindexBuffer; // Index buffer for colour cube
		unsigned int m_TPindexBuffer; // Index buffer for texture Phong cube
		unsigned int m_FCprogram; // Flat colour shader ID
		unsigned int m_TPprogram; // Textured Phong shader ID
		unsigned int m_numberTexture; // Texture ID
		unsigned int m_letterTexture; // Texture ID
		unsigned int m_textureSlots[2]; // Slot where the textures are stored
		bool m_goingUp = false; // Is the cude going up?
		float m_timeSummed = 10.f; // How much timer has elasped?
#pragma endregion TempVars

		
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(EventBaseClass& e); //!< Called when an event happens
		inline Window& GetWindow() { return *m_Window; }
		inline static float getTimestep() { return s_timestep; }
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}