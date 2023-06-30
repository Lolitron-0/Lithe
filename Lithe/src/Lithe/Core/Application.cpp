#include "ltpch.h"
#include "Application.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"
#include <glad/glad.h>
#include "Base.hpp"

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

        Ra::Camera cam{{0, 1, 5}, -90, 0, 16.f / 9.f};
        m_CameraController = std::make_shared<FlyCameraController>(cam);

        float data[] = {
            // front
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
        };

        m_VertexArray = Ra::VertexArray::Create();

        m_VertexBuffer = Ra::VertexBuffer::Create(data, sizeof(data));
        Ra::BufferLayout layout = {
            {Ra::UniformDataType::Float3, "position"},
        };
        m_VertexBuffer->SetLayout(layout);

        unsigned int indices[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };
        m_IndexBuffer = Ra::IndexBuffer::Create(indices, 36);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_TestShader = Ra::Shader::Create(
            R"(G:\dev\Lithe\Lithe\src\Lithe\Core\test.vert)",
            R"(G:\dev\Lithe\Lithe\src\Lithe\Core\test.frag)");
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

            Ra::RenderCommand::SetClearColor({ 1.f, 0.f, 1.f, 0.f });
            Ra::RenderCommand::Clear();

            m_MainWindow->PullEvents();

            m_CameraController->OnUpdate();

            for (const LayerPtr& layer : m_LayerStack)
                layer->OnUpdate();



            Ra::Renderer::BeginScene(m_CameraController->GetCamera());

            Ra::Renderer::Submit(m_VertexArray, m_TestShader);

            Ra::Renderer::EndScene();

            m_ImGuiLayer->Begin();


            for (const LayerPtr& layer : m_LayerStack)
                layer->OnImGuiDraw();

            m_ImGuiLayer->End();

            GLenum err;
            while ((err = glGetError()) != GL_NO_ERROR)
            {
                LITHE_LOG_CORE_DEBUG(err);
            }
            m_MainWindow->OnUpdate();
        }
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<WindowClosedEvent>(LT_BIND_EVENT_FN(Application::OnWindowClosed));
        dispatcher.Dispatch<WindowResizedEvent>(LT_BIND_EVENT_FN(Application::OnWindowResized));

        m_CameraController->OnEvent(event);

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

    const Window& Application::GetWindow() const
    {
        return *m_MainWindow;
    }

}