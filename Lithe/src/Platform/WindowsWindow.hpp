#pragma once
#include "Lithe/Core/Window.hpp"
#include "GLFW/glfw3.h"

namespace Lithe
{
	///Specialisation for a Windows window.
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return data_.Width; };
		unsigned int GetHeight() const override { return data_.Height; };

		virtual bool IsVSync() const override { return data_.VSync; }
		virtual void SetVSync(bool val) override;

		void SetEventCallback(EventCallbackFn& callback) override { data_.EventCallback = callback; };
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

