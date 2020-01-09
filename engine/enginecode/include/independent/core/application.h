/** \file application.h
*/
#pragma once

#include "../events/WindowEvents.h"
#include "../events/KeyEvents.h"
#include "../events/MouseEvents.h"
#include "systems/MyLogger.h"
#include "systems/MyTimer.h"
#include "windows/window.h"

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

		
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(EventBaseClass& e); //!< Called when an event happens
		inline Window& GetWindow() { return *m_Window; }
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}