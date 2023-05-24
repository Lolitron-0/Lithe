#include "Application.h"
#include "Log.hpp"

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
		LITHE_CORE_WARN("Logger initialised!");
		while (true);
	}
}