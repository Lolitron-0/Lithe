#pragma once
#include "Log.hpp"

#ifdef LT_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Lithe::CreateApplication();
	app->Run();
	LITHE_CORE_TRACE("Shutting down...");
	delete app;
	LITHE_CORE_INFO("Exited successfully!");
}

#endif // LT_PLATFORM_WINDOWS

