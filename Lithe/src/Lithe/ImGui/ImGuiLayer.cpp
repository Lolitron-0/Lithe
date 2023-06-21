#include "ltpch.h"
#include "ImGuiLayer.hpp"
#include "Lithe/Core/Application.hpp"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

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
        EventDispatcher dispatcher{ event };
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        const auto& app = Application::GetInstance();
        io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
        m_Time = time;

        static bool show{ true };
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        GLFWwindow* window{ Application::GetInstance().GetWindow().GetNativeHandle<GLFWwindow*>() };
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        LITHE_CORE_TRACE("ImGui attached");
    }

    void ImGuiLayer::OnDetach()
    {
    }
}
