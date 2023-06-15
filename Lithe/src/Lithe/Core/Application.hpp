/*****************************************************************//**
 * @file   Application.hpp
 * @brief  Application class header
 * 
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/
#pragma once
#include "Base.hpp"
#include "Lithe/Events/Events.hpp"
#include "LayerStack.hpp"
#include "Lithe/Utils/Singleton.hpp"

namespace Lithe
{
	/**
	 * @brief Base class for all applications
	 */
	class LITHE_API Application : Singleton<Application>
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
			return layerStack_.PushLayer<T>(std::forward<T>(args)...);
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
			return layerStack_.PushOverlay<T>(std::forward<T>(args)...);
		}

	private:
		void OnEvent(Event& event);

		bool OnWindowClosed(const WindowClosedEvent& event);
		bool OnWindowResized(const WindowResizedEvent& event);

	private:
		LayerStack layerStack_;
		bool running_{ true };
	};

	///Defined in client
	Application* CreateApplication();
}
