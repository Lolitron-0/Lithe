#include "ltpch.h"
#include "Application.h"
#include "Log.hpp"
#include "Events/Events.hpp"

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
		Log::Init();

		MouseMovedEvent e{14.3, 195.02};
		LITHE_CORE_DEBUG(e);

		while (true);
	}
}