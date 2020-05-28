/** \file WindowsInput.h
*/
#pragma once
#include "systems/Input.h"

namespace Engine {
	/**
\class WindowsInput
Implementaion of Input base class
*/
	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}