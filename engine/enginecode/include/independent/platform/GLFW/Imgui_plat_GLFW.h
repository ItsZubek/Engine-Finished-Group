#pragma once
#include "include/independent/UI/imgui_impl.h"
#include <GLFW/glfw3.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Engine {
	class ImguiGLFW : public Imgui {
	public:
		ImguiGLFW();
		~ImguiGLFW();

		void gen(std::shared_ptr<Window> window) override;

		void createFrames() override;
		void render() override;
		void close() override;
	};
}