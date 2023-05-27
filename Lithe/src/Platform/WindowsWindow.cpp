#include "ltpch.h"
#include "WindowsWindow.hpp"
#include "Lithe/Core/Log.hpp"
#include "Lithe/Core/Assert.hpp"

namespace Lithe
{
	static bool glfwInitialised_ = false;

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void Lithe::WindowsWindow::OnUpdate()
	{
		glfwSwapBuffers(handle_);
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		if (!glfwInitialised_)
		{
			LITHE_CORE_TRACE("Started GLFW initialisation...");

			int success = glfwInit();
			LITHE_CORE_ASSERT(success, "GLFW initalisation failed");

			glfwInitialised_ = true;
		}
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(handle_);
	}

	void WindowsWindow::SetVSync(bool val)
	{
	}

}