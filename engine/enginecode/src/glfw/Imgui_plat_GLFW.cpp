#include "engine_pch.h"
#include "include/independent/platform/GLFW/Imgui_plat_GLFW.h"
#include "include/independent/UI/Imgui_impl.h"

namespace Engine {
	ImguiGLFW::ImguiGLFW() {

	}

	ImguiGLFW::~ImguiGLFW() {

	}

	void ImguiGLFW::gen(std::shared_ptr<Window> window) {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		

		// Set ImGui style
		ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->getNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void ImguiGLFW::createFrames() {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiGLFW::render() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImguiGLFW::close() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	Imgui* Imgui::initialise()
	{
		return new ImguiGLFW();
	}
};
