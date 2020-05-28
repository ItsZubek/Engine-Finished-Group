
#include "engine_pch.h"
#include "ImGUI/ImGUILayer.h"
#include "imgui.h"

namespace Engine
{
	IMGUILayer::IMGUILayer() : Layer("IMGUI Layer")
	{

	}
	IMGUILayer::~IMGUILayer()
	{

	}
	void IMGUILayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags != ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags != ImGuiBackendFlags_HasSetMousePos;

		IMGUI_IMPL_API("# version 410");
	}
	void IMGUILayer::OnDetach()
	{

	}
	void IMGUILayer::OnUpdate(float timestep)
	{
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui::GetDrawData();
	}
	void IMGUILayer::OnEvent(EventBaseClass& e)
	{
	}
}
