#include "Application.hpp"
#include "Log.hpp"
#include "Platform/WindowsWindow.hpp"
#include <glad/glad.h>

namespace Lithe
{

	Lithe::Application::Application()
	{
	}

	Lithe::Application::~Application()
	{
		LITHE_CORE_TRACE("Freing memory...");
	}

	void Lithe::Application::Run()
	{
		running_ = true;
		Log::Init();
		auto mainWindow{ Window::Create() };
		mainWindow->SetEventCallback(LT_BIND_EVENT_FN(Application::OnEvent));

		while (running_)
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (LayerPtr layer : layerStack_)
				layer->OnUpdate();

			mainWindow->OnUpdate();
		}
	}
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };
		dispatcher.Dispatch<WindowClosedEvent>(LT_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(LT_BIND_EVENT_FN(Application::OnWindowResized));

		LITHE_CORE_TRACE(event);

		for (auto it = layerStack_.rbegin(); it != layerStack_.rend(); it++)
		{
			if (event.Handled)
				break;
			(*it)->OnEvent(event);
		}
	}

	bool Application::OnWindowClosed(const WindowClosedEvent& event)
	{
		running_ = false;
		return true; // Client should do all shutdown stuff in destructor 
	}

	bool Application::OnWindowResized(const WindowResizedEvent& event)
	{
		return false;
	}


}