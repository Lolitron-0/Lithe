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
	///Specialisation for a Windows window.
	class LITHE_API WindowsWindow final : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; };
		unsigned int GetHeight() const override { return m_Data.Height; };

		virtual std::any getNativeHandleImpl_() const override;

		virtual bool IsVSync() const override;
		virtual void SetVSync(bool val) override;

		void MaximizeWindow() const override;
		void MinimizeWindow() const override;

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; };
	private:
		void Init(const WindowProperties& props);
		void Shutdown();
	private:

		GLFWwindow* m_Handle;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}

