#include "ltpch.h"
#include "Application.h"
#include "Log.hpp"
#include "Lithe/Events/Events.hpp"

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

		while (true);
	}
}