#include "ImGuiLayer.hpp"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace Lithe
{

	ImGuiLayer::ImGuiLayer()
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
	}

	void ImGuiLayer::OnUpdate()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();



		ImGui_ImplGlfw_InitForOpenGL(, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}
	void ImGuiLayer::OnDetach()
	{
	}
}
