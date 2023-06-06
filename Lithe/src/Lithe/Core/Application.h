#pragma once
#include "Base.hpp"
#include "Lithe/Events/Events.hpp"

namespace Lithe 
{
	class LITHE_API Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		void OnEvent(Event& event);

		bool OnWindowClosed(const WindowClosedEvent& event);
		bool OnWindowResized(const WindowResizedEvent& event);

	private:
		bool running_;
	};

	//Defined in client
	Application* CreateApplication();
}
