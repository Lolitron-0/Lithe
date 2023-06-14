/*****************************************************************//**
 * \file   WindowsWindow.hpp
 * \brief  WindowsWindow header
 *
 * \author Lolitron
 * \date   June 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Core/Window.hpp"
#include <GLFW/glfw3.h>


namespace Lithe
{
	///Specialisation for a Windows window.
	class LITHE_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return data_.Width; };
		unsigned int GetHeight() const override { return data_.Height; };

		virtual bool IsVSync() const override;
		virtual void SetVSync(bool val) override;

		void SetEventCallback(const EventCallbackFn& callback) override { data_.EventCallback = callback; };
	private:
		void Init(const WindowProperties& props);
		void Shutdown();
	private:

		GLFWwindow* handle_;

		struct WindowData {
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData data_;
	};
}

