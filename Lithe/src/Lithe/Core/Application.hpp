/*****************************************************************//**
 * @file   Application.hpp
 * @brief  Application class header
 *
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/
#pragma once
#include "Lithe/Events/Events.hpp"
#include "Window.hpp"
#include "Lithe/Utils/Singleton.hpp"
#include "LayerStack.hpp"
#include "Lithe/ImGui/ImGuiLayer.hpp"
#include "Lithe/Input/CameraController.hpp"

namespace Lithe
{
    /**
     * @brief Base class for all applications
     */
    class LITHE_API Application : public Singleton<Application>
    {
    public:
        Application(Ra::RendererAPI::API renderingApi = Ra::RendererAPI::API::OpenGL);
        virtual ~Application();

        /// Starts main cycle
        void Run();
        /// Asks application instance to end cycle
        void Close();

        /**
         * @brief Wrapper around LayerStack corresponding method.
         * See LayerStack::PushLayer for more information
         */
        void PushLayer(LayerPtr layer)
        {
            return m_LayerStack.PushLayer(layer);
        }

        /**
        * @brief Wrapper around LayerStack corresponding methods.
        * See LayerStack::PushLayer for more information
        */
        void PushOverlay(LayerPtr layer)
        {
            return m_LayerStack.PushOverlay(layer);
        }

        Window& GetWindow() const;

    private:
        void OnEvent(Event& event);

        bool OnWindowClosed(const WindowClosedEvent& event);
        bool OnWindowResized(const WindowResizedEvent& event);

        static void OnRendererError_(const std::string& errorMessage);

    private:
        LayerStack m_LayerStack;
        Scope<Window> m_MainWindow;
        Ref<ImGuiLayer> m_ImGuiLayer;
        bool m_Running{ true };

        double m_LastFrameTimeSec{ 0.0 };
    };

    ///Defined in client
    Application* CreateApplication();
}
