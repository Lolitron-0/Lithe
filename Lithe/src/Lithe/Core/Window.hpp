/*****************************************************************//**
 * @file   Window.hpp
 * @brief  Window class header
 *
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Events/Event.hpp"
#include <functional>
#include <any>

namespace Lithe
{
	/**
	 * @brief Class (or struct even) that contains general data needed to construct a window.
	 */
	struct LITHE_API WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string title = "Lithe Engine",
			unsigned int width = 1920,
			unsigned int height = 1080)
			:Title(title), Width(width), Height(height)
		{}
	};


	/**
	 * Platform independent window interface.
	 */
	class LITHE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual void MaximizeWindow() const = 0;
		virtual void MinimizeWindow() const = 0;

		/**
		 * @brief Getter for backend dependent handle (e.g. GLFWwindow*)
		 * @tparam Handle type
		 * @return Hanldle
		*/
		template<typename T>
		T GetNativeHandle() const {
			return std::any_cast<T>(getNativeHandleImpl_());
		}

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool val) = 0;

		/**
		 * @brief Set main event callback function.
		 *
		 * It will be called on every event and intended to dispatch to other callbacks
		 * @param callback
		 */
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/**
		 * @brief Factory method to create platform independent window.
		 *
		 * @param props - Window properties
		 * @return Pointer to base class Window, that contains platform specific data
		 */
		static Scope<Window> Create(const WindowProperties& props = WindowProperties());
	protected:

		virtual std::any getNativeHandleImpl_() const = 0;

		Window() = default;
	};

}
