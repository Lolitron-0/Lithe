#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv)
{
	Lithe::Application* app{ Lithe::CreateApplication() };
	app->Run();
	LITHE_CORE_LOG_TRACE("Shutting down...");
	delete app;
	LITHE_CORE_LOG_INFO("Exited successfully!");
}

#endif // LT_PLATFORM_WINDOWS

