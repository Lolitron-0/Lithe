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

		float data[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.f,   0.5f, 0.0f
		};
		
		m_VertexArray = Ra::VertexArray::Create();

		m_VertexBuffer = Ra::VertexBuffer::Create(data, sizeof(data));
		Ra::BufferLayout layout = {
			{Ra::UniformDataType::Float3, "position"},
		};
		m_VertexBuffer->SetLayout(layout);

		unsigned int indices[3] = {0,1,2};
		m_IndexBuffer = Ra::IndexBuffer::Create(indices, 3);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_TestShader = Ra::Shader::Create(
            R"(C:\Users\niten01\Projects\Lithe\Lithe\src\Lithe\Core\test.vert)",
            R"(C:\Users\niten01\Projects\Lithe\Lithe\src\Lithe\Core\test.frag)");
	}

	Lithe::Application::~Application()
	{
		LITHE_LOG_CORE_TRACE("Freing memory...");
	}

	void Lithe::Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			Ra::RenderCommand::SetClearColor({ 1.f, 1.f, 0.f, 0.f });
			Ra::RenderCommand::Clear();

			m_MainWindow->PullEvents();
			
			for (const LayerPtr& layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (const LayerPtr& layer : m_LayerStack)
				layer->OnImGuiDraw();

			m_ImGuiLayer->End();

			m_TestShader->Bind();
			Ra::RenderCommand::DrawIndexed(m_VertexArray, 3);

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
		glViewport(0,0, event.GetNewWidth(), event.GetNewHeight());
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