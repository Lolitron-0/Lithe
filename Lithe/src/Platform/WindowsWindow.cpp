#include "WindowsWindow.hpp"
#include "Lithe/Core/Log.hpp"
#include "Lithe/Core/Assert.hpp"
#include "Lithe/Events/Events.hpp"

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
		glfwPollEvents();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		data_.Width = props.Width;
		data_.Height = props.Height;
		data_.Title = props.Title;

		if (!glfwInitialised_)
		{
			LITHE_CORE_TRACE("Initialising GLFW for the first time...");

			int success = glfwInit();
			LITHE_CORE_ASSERT(success, "GLFW initalisation failed");

			glfwInitialised_ = true;
			LITHE_CORE_INFO("Initialised GLFW!");
		}

		handle_ = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		LITHE_CORE_ASSERT(handle_, "GLFWwindow instance not created!");

		LITHE_CORE_TRACE("Created GLFWwindow instance.");

		glfwSetWindowUserPointer(handle_, &data_);
		SetVSync(true);

		glfwSetWindowCloseCallback(handle_, [](GLFWwindow* window) 
		{
			WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowClosedEvent event{};
			data.EventCallback(event);
		});

		glfwSetWindowSizeCallback(handle_, [](GLFWwindow* window, int width, int height) 
		{
			WindowData& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizedEvent event{static_cast<unsigned int>(width), static_cast<unsigned int>(height)};
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(handle_);
	}

	void WindowsWindow::SetVSync(bool val)
	{
	}

}