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

	private:
		LayerStack m_LayerStack;
		Scope<Window> m_MainWindow;
		Ref<ImGuiLayer> m_ImGuiLayer;
		bool m_Running{ true };

		Ref<Ra::VertexBuffer> m_VertexBuffer;

		unsigned int m_VertexData;
		unsigned int m_VertexArray;
		unsigned int m_IndexBuffer;
	};

	///Defined in client
	Application* CreateApplication();
}
