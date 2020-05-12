#pragma once

#include "include/independent/windows/window.h"
#include "imgui.h"

namespace Engine {
	class Imgui
	{
	public:
		static Imgui* initialise(); //!< Static create function to return a Window pointer in our platform specific implementation

		virtual void gen(std::shared_ptr<Window> window) = 0;
		virtual void createFrames() = 0;
		virtual void render() = 0;
		virtual void close() = 0;
	};
}

