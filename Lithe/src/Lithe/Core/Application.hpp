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

		/// Start main cycle
		void Run();

		/**
		 * @brief Wrapper around LayerStack corresponding method.
		 * See LayerStack::PushLayer for more information
		 * 
		 * @param ...args  Arguments for layer creation
		 * @return Smart pointer object containing created layer
		 */
		template <class T, class... Args>
		LayerPtr PushLayer(Args&&... args)
		{
			return m_LayerStack.PushLayer<T>(std::forward<T>(args)...);
		}

		/**
		* @brief Wrapper around LayerStack corresponding methods.
		* See LayerStack::PushLayer for more information
		*
		* @param ...args  Arguments for layer creation
		* @return Smart pointer object containing created layer
		*/
		template <class T, class... Args>
		LayerPtr PushOverlay(Args&&... args)
		{
			return m_LayerStack.PushOverlay<T>(std::forward<T>(args)...);
		}

		const Window& GetWindow() const;

	private:
		void OnEvent(Event& event);

		bool OnWindowClosed(const WindowClosedEvent& event);
		bool OnWindowResized(const WindowResizedEvent& event);

	private:
		LayerStack m_LayerStack;
		Scope<Window> m_MainWindow;
		bool m_Running{ true };
	};

	///Defined in client
	Application* CreateApplication();
}
