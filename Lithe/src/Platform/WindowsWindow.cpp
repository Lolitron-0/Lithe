#include "WindowsWindow.hpp"
#include "Lithe/Core/Assert.hpp"
#include "Lithe/Events/Events.hpp"
#include <glad/glad.h>

namespace Lithe
{

	static bool glfwInitialised{ false };
	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props)
	{
		data_.Width = props.Width;
		data_.Height = props.Height;
		data_.Title = props.Title;

		if (!glfwInitialised)
		{
			LITHE_CORE_TRACE("Initialising GLFW for the first time...");

			int success{ glfwInit() };
			LITHE_CORE_ASSERT(success, "GLFW initalisation failed");

			glfwInitialised = true;
			LITHE_CORE_INFO("Initialised GLFW!");
		}

		handle_ = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
		LITHE_CORE_ASSERT(handle_, "GLFWwindow instance not created!");

		LITHE_CORE_TRACE("Created GLFWwindow instance.");

		//TODO: will be replaced with rendering context
		glfwMakeContextCurrent(handle_);

		int status{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
		LITHE_CORE_ASSERT(status, "Failed to initialize Glad!");
		std::string version{ (const char*)glGetString(GL_VERSION) };
		LITHE_CORE_INFO("OpenGL loaded version: {0}", version);

		glfwSetWindowUserPointer(handle_, &data_);
		SetVSync(true);

		glfwSetWindowCloseCallback(handle_, [](GLFWwindow* window)
			{
				WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
				WindowClosedEvent event{};
				data.EventCallback(event);
			});

		glfwSetWindowSizeCallback(handle_, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
				data.Width = width;
				data.Height = height;

				WindowResizedEvent event{ static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
				data.EventCallback(event);
			});

	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(handle_);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(handle_);
	}

	bool WindowsWindow::IsVSync() const { return data_.VSync; }

	void WindowsWindow::SetVSync(bool val)
	{
		if (val)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data_.VSync = val;
	}

}
