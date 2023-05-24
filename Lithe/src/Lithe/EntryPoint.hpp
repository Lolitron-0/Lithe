#pragma once

#ifdef LT_PLATFORM_WINDOWS

extern Lithe::Application* Lithe::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Lithe::CreateApplication();
	app->Run();
	delete app;
}

#endif // LT_PLATFORM_WINDOWS

