#pragma once
#include "Log.hpp"

#ifdef LT_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv)
{
	Lithe::Application* app{ Lithe::CreateApplication() };
	app->Run();
	LITHE_LOG_CORE_TRACE("Shutting down...");
	delete app;
	LITHE_LOG_CORE_INFO("Exited successfully!");
}

#endif // LT_PLATFORM_WINDOWS

