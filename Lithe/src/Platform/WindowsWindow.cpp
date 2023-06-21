#include "WindowsWindow.hpp"
#include "Lithe/Core/Assert.hpp"
#include "Lithe/Events/Events.hpp"
#include "WindowsMouse.hpp"
#include "WindowsKeyboard.hpp"
#include <glad/glad.h>

namespace Lithe
{
    Mouse* Mouse::s_Instance = new WindowsMouse();
    Keyboard* Keyboard::s_Instance = new WindowsKeyboard();

    static bool s_GlfwInitialised{ false };

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
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        m_Data.Title = props.Title;

        if (!s_GlfwInitialised)
        {
            LITHE_CORE_TRACE("Initialising GLFW for the first time...");

            int success{ glfwInit() };
            LITHE_CORE_ASSERT(success, "GLFW initalisation failed");

            s_GlfwInitialised = true;
            LITHE_CORE_INFO("Initialised GLFW!");
        }

        m_Handle = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        LITHE_CORE_ASSERT(m_Handle, "GLFWwindow instance not created!");

        LITHE_CORE_TRACE("Created GLFWwindow instance.");

        //TODO: will be replaced with rendering context
        glfwMakeContextCurrent(m_Handle);

        int status{ gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) };
        LITHE_CORE_ASSERT(status, "Failed to initialize Glad!");
        std::string version{ (const char*)glGetString(GL_VERSION) };
        LITHE_CORE_INFO("OpenGL loaded version: {0}", version);

        glfwSetWindowUserPointer(m_Handle, &m_Data);
        SetVSync(true);

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
                WindowClosedEvent event{};
                data.EventCallback(event);
            });

        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
                data.Width = width;
                data.Height = height;

                WindowResizedEvent event{ static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };

                MouseMovedEvent event{ static_cast<float>(xPos), static_cast<float>(yPos) };
                data.EventCallback(event);
            });

        glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event{ FromGlfwMouseButton(button) };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonPressedEvent event{ FromGlfwMouseButton(button) };
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                }

            });
        glfwSetKeyCallback(m_Handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event{ FromGlfwKey(key), false };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event{ FromGlfwKey(key), true };
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event{ FromGlfwKey(key) };
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
                }
            });
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Handle);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Handle);
    }

    void WindowsWindow::MaximizeWindow() const
    {
        glfwMaximizeWindow(m_Handle);
    }

    void WindowsWindow::MinimizeWindow() const
    {
        glfwIconifyWindow(m_Handle);
    }

    std::any WindowsWindow::getNativeHandleImpl_() const
    {
        return std::any(m_Handle);
    }

    bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

    void WindowsWindow::SetVSync(bool val)
    {
        if (val)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = val;
    }

}
