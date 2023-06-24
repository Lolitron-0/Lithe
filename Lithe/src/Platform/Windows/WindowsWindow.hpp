/*****************************************************************//**
 * @file   WindowsWindow.hpp
 * @brief  WindowsWindow header
 *
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Window.hpp"
#include <GLFW/glfw3.h>


namespace Lithe
{
    ///Specialization for a Windows window.
    class LITHE_API WindowsWindow final : public Window
    {
    public:
        using EventQueue = std::queue<Ref<Event>>;

        WindowsWindow(const WindowProperties& props);

        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; };
        unsigned int GetHeight() const override { return m_Data.Height; };

        std::any getNativeHandleImpl_() const override;

        bool IsVSync() const override;
        void SetVSync(bool val) override;

        void MaximizeWindow() const override;
        void MinimizeWindow() const override;

        void PushEvent(Ref<Event>& event) override;
        void PullEvents() override;

        void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
    private:
        void Init(const WindowProperties& props);
        void Shutdown();
    private:

        GLFWwindow* m_Handle;

        struct WindowData {
            using EventQueue_t = EventQueue;

            std::string Title;
            unsigned int Width;
            unsigned int Height;
            bool VSync;

            EventCallbackFn EventCallback;
            EventQueue_t EventQueue;
        };

        WindowData m_Data;
    };
}

