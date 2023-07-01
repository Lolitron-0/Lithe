#include "ltpch.h"
#include "Platform.hpp"
#include "Timestep.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"
#include <glad/glad.h>

namespace Lithe
{

    Lithe::Application::Application()
    {
        Ra::SetErrorCallback(Application::OnRendererError_);
        Ra::Renderer::SetAPI(Ra::RendererAPI::API::OpenGL);

        Log::Init();

        m_MainWindow = Window::Create();
        m_MainWindow->SetEventCallback(LT_BIND_EVENT_FN(Application::OnEvent));
        m_MainWindow->MaximizeWindow();  // Needed to send initial resize event

        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        m_LayerStack.PushOverlay(m_ImGuiLayer);

        Ra::Renderer::Init();

    }

    Lithe::Application::~Application()
    {
        LITHE_LOG_CORE_TRACE("Freing memory...");
        Ra::Renderer::Shutdown();
    }

    void Lithe::Application::Run()
    {
        m_Running = true;

        while (m_Running)
        {
            double time = Platform::GetTime();
            Timestep ts = time - m_LastFrameTimeSec;
            m_LastFrameTimeSec = time;

            m_MainWindow->PullEvents();

            for (const LayerPtr& layer : m_LayerStack)
                layer->OnUpdate(ts);

            m_ImGuiLayer->Begin();


            for (const LayerPtr& layer : m_LayerStack)
                layer->OnImGuiDraw();

            m_ImGuiLayer->End();

            m_MainWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<WindowClosedEvent>(LT_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizedEvent>(LT_BIND_EVENT_FN(Application::OnWindowResized));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); it++)
        {
            if (event.Handled)
                break;
            (*it)->OnEvent(event);
        }
    }

    bool Application::OnWindowClosed(const WindowClosedEvent& event)
    {
        m_Running = false;
        return true; // Client should do all shutdown stuff in destructor 
    }

    bool Application::OnWindowResized(const WindowResizedEvent& event)
    {
        glViewport(0, 0, event.GetNewWidth(), event.GetNewHeight());
        return false;
    }

    void Application::OnRendererError_(const std::string& errorMessage)
    {
        LITHE_LOG_CORE_ERROR(errorMessage);
    }

    Window& Application::GetWindow() const
    {
        return *m_MainWindow;
    }

}