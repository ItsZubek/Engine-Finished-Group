/** \file Input.h
*/
#pragma once

namespace Engine {
	/**
\class Input
Base class for all input implementations
*/
	class Input
	{
	public:
		inline static bool isKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); } //!< Function that checks if the key is pressed
		inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); } //!< Function that checks if the Mouse Button is pressed
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); } //!< Function that checks Mouse position on X axis
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); } //!< Function that checks Mouse position on Y axis

		//Implementation functions used in the functions above
	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;

	};

}