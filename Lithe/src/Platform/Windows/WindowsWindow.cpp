#include "ltpch.h"
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
            LITHE_LOG_CORE_TRACE("Initializing GLFW for the first time...");

            int success{ glfwInit() };
            LITHE_CORE_ASSERT(success, "GLFW initialization failed");

            s_GlfwInitialised = true;
            LITHE_LOG_CORE_INFO("Initialized GLFW!");
        }

        glfwWindowHint(GLFW_SAMPLES, 4); /// @todo runtime switch

        m_Handle = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        LITHE_CORE_ASSERT(m_Handle, "GLFWwindow instance not created!");

        LITHE_LOG_CORE_TRACE("Created GLFWwindow instance.");

        m_RenderingContext = Ra::RenderingContext::Create(m_Handle);

        HideCursor();

        LITHE_CORE_ASSERT(m_RenderingContext->IsLoaded(), "Failed to initialize Glad!");
        auto info = m_RenderingContext->GetInfo();
        LITHE_LOG_CORE_DEBUG("OpenGL info:");
        LITHE_LOG_CORE_DEBUG("Vendor: {0}", info.Vendor);
        LITHE_LOG_CORE_DEBUG("Renderer: {0}", info.Renderer);
        LITHE_LOG_CORE_DEBUG("Version: {0}", info.Version);
        auto version = std::any_cast<gladGLversionStruct>(info.NativeInfo);
        LITHE_CORE_ASSERT(version.major > 4 || (version.major == 4 && version.minor >= 5), "Lithe needs at least OpenGL version 4.5!");

        LITHE_LOG_CORE_INFO("Created OpenGL rendering context!");

        glfwSetWindowUserPointer(m_Handle, &m_Data);
        SetVSync(true);

        glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* window)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
                auto event = std::make_shared<WindowClosedEvent>();
                data.EventQueue.push(event);
            });

        glfwSetWindowSizeCallback(m_Handle, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
                data.Width = width;
                data.Height = height;

                auto event = std::make_shared<WindowResizedEvent>(static_cast<unsigned int>(width), static_cast<unsigned int>(height));
                data.EventQueue.push(event);
            });

        glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };

                auto event = std::make_shared <MouseMovedEvent>( static_cast<float>(xPos), static_cast<float>(yPos) );
                data.EventQueue.push(event);
            });

        glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };

                switch (action)
                {
                case GLFW_PRESS:
                {
                    auto event = std::make_shared <MouseButtonPressedEvent>( FromGlfwMouseButton(button) );
                    data.EventQueue.push(std::move(event));
                    break;
                }
                case GLFW_RELEASE:
                {
                    auto event = std::make_shared <MouseButtonReleasedEvent>( FromGlfwMouseButton(button) );
                    data.EventQueue.push(std::move(event));
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
                    auto event = std::make_shared <KeyPressedEvent>( FromGlfwKey(key), false );
                    data.EventQueue.push(std::move(event));
                    break;
                }
                case GLFW_REPEAT:
                {
                    auto event = std::make_shared <KeyPressedEvent>( FromGlfwKey(key), true );
                    data.EventQueue.push(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    auto event = std::make_shared <KeyReleasedEvent>(FromGlfwKey(key));
                    data.EventQueue.push(event);
                    break;
                }
                default:
                    break;
                }
            });

        glfwSetScrollCallback(m_Handle, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data{ *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)) };
            auto event = std::make_shared<MouseScrolledEvent>( static_cast<float>(xOffset), static_cast<float>(yOffset) );
            data.EventQueue.push(event);
            });
    }

    void WindowsWindow::OnUpdate()
    {
        m_RenderingContext->SwapBuffers();
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Handle);
    }

    void WindowsWindow::MaximizeWindow()
    {
        glfwMaximizeWindow(m_Handle);
    }

    void WindowsWindow::MinimizeWindow() 
    {
        glfwIconifyWindow(m_Handle);
    }

    void WindowsWindow::ShowCursor()
    {
        glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void WindowsWindow::HideCursor()
    {
        glfwSetInputMode(m_Handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    bool WindowsWindow::IsCursorHidden() const
    {
        return glfwGetInputMode(m_Handle, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
    }

    void WindowsWindow::PushEvent(Ref<Event>& event)
    {
        m_Data.EventQueue.push(event);
    }

    void WindowsWindow::PullEvents()
    {
        glfwPollEvents();

        while (!m_Data.EventQueue.empty())
        {
            m_Data.EventCallback(std::move(*m_Data.EventQueue.front()));
            m_Data.EventQueue.pop();
        }
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
