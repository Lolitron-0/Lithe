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
		Application();
		virtual ~Application();

		/// Starts main cycle
		void Run();

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

		const Window& GetWindow() const;

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

		Ref<Ra::Shader> m_TestShader;
		Ref<Ra::VertexBuffer> m_VertexBuffer;
		Ref<Ra::IndexBuffer> m_IndexBuffer;
		Ref<Ra::VertexArray> m_VertexArray;
		Ref<FlyCameraController> m_CameraController;
	};

	///Defined in client
	Application* CreateApplication();
}
