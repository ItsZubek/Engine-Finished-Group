/** \file application.h
*/
#pragma once


#include "systems/MyLogger.h"
#include "systems/MyTimer.h"
#include "windows/window.h"

#include "events/KeyEvents.h"
#include "events/MouseEvents.h"
#include "events/WindowEvents.h"

#include <glm/glm.hpp>

#include "Layer/LayerStack.h"

#include <Box2D/Box2D.h>
#include "UI/imgui_impl.h"
#include "imgui.h"






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
		
		std::shared_ptr<MyLogger> mp_logger; //!< Shared Pointer to a logger
		std::shared_ptr<MyTimer> mp_timer;//!< Shared Pointer to a timer
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<LayerStack> m_layerStack;

		
	private:
		static Application* s_instance; //!< Singleton instance of the application
		static float s_timestep; //!< last frame timestep

		bool m_running = true; //!< Is the application running?
		
		std::shared_ptr<imgui> mp_imgui; //!< Shared Pointer to ImGui

		b2World* boxWorld = nullptr;
		b2Vec2 m_gravity = b2Vec2(0.f, 0.f);

		const int m_iVelIterations = 7;
		const int m_iPosIterations = 5;
		
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