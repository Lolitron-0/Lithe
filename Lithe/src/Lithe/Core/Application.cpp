#include "Application.h"
#include "Log.hpp"
#include "Platform/WindowsWindow.hpp"

namespace Lithe 
{

	Lithe::Application::Application()
	{
	}

	Lithe::Application::~Application()
	{
		LITHE_CORE_INFO("Freing memory...");
	}

	void Lithe::Application::Run()
	{
		running_ = true;
		Log::Init();
		auto mainWindow = Window::Create();
		mainWindow->SetEventCallback(LT_BIND_EVENT_FN(Application::OnEvent));

		while (running_)
		{
			mainWindow->OnUpdate();
		}
	}
	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher{ event };
		dispatcher.Dispatch<WindowClosedEvent>(LT_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(LT_BIND_EVENT_FN(Application::OnWindowResized));
	}

	bool Application::OnWindowClosed(const WindowClosedEvent& event)
	{
		running_ = false;
		return true;
	}

	bool Application::OnWindowResized(const WindowResizedEvent& event)
	{
		LITHE_CORE_DEBUG(event);
		return false;
	}


}