#include "ltpch.h"
#include "Application.hpp"
#include "Window.hpp"
#include "LayerStack.hpp"
#include <glad/glad.h>

namespace Lithe
{

	Lithe::Application::Application()
	{
		Log::Init();
		m_MainWindow = Window::Create();
		m_MainWindow->SetEventCallback(LT_BIND_EVENT_FN(Application::OnEvent));
		m_MainWindow->MaximizeWindow();  // Needed to send initial resize event

		m_ImGuiLayer = std::make_shared<ImGuiLayer>();
		m_LayerStack.PushOverlay(m_ImGuiLayer);

		float data[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.f,   0.5f, 0.0f
		};

		glGenVertexArrays(1,&m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexData);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexData);
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), &data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		unsigned int indices[3] = {0,1,2};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
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
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_MainWindow->PullEvents();
			
			for (LayerPtr layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();

			for (LayerPtr layer : m_LayerStack)
				layer->OnImGuiDraw();

			m_ImGuiLayer->End();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
		return false;
	}

	const Window& Application::GetWindow() const
	{
		return *m_MainWindow;
	}

}