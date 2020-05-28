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
#include "windows/Shader.h"
#include "windows/Buffer.h"
#include "windows/Texture.h"
#include "windows/OrthographicCamera.h"

#include "Audio/AudioManager.h"

#include <vector>
#include "Physics/PlayerShape.h"
#include "Layer/LayerStack.h"

#include "UI/imgui_impl.h"

#include "Physics/PlayerShape.h"
#include "AI/ship.h"
#include "Physics/Object.h"
#include "Physics/BulletShape.h"
#include "Physics/Collisions.h"



#include <Box2D/Box2D.h>





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
		std::shared_ptr<MyTimer> mp_timer; //!< Shared Pointer to a timer
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<LayerStack> m_layerStack;
	private:
		static Application* s_instance; //!< Singleton instance of the application
		
		std::shared_ptr<Imgui> mp_imgui; //!< Shared Pointer to ImGui

		

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
		 //!< Pointer to a window class
		static glm::ivec2 s_screenResolution; //!< Screen resolution
		static float s_timestep; //!< last frame timestep

		AudioManager m_audiosystem;

		b2World* boxWorld = nullptr;
		b2Vec2 m_gravity = b2Vec2(0.f, 0.f);

		std::shared_ptr<Engine::PlayerShape> m_Player;
		std::vector<std::shared_ptr<Engine::Ship>> m_Enemies;
		std::shared_ptr<Engine::BulletShape> m_Bullet;
		Engine::Collisions m_CollisionListener;

		const int m_iVelIterations = 7;
		const int m_iPosIterations = 5;

		OrthographicCamera m_Camera; //!< Orthographic Camera

		/*b2World* boxWorld = nullptr;
		b2Vec2 m_gravity = b2Vec2(0.f, 0.f);

		std::shared_ptr<PlayerShape> m_Player; //!< the player in the game
		//b2Vec2 m_vertices;
		const int m_iVelIterations = 7;
		const int m_iPosIterations = 5;*/

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

		
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		void run(); //!< Main loop
		void onEvent(EventBaseClass& e); //!< Called when an event happens
		inline Window& GetWindow() { return *m_Window; } //!< Window Getter
		inline static float getTimestep() { return s_timestep; } //!< TimeStep Getter
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook

}