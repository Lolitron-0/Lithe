#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Events/Event.hpp"


namespace Lithe
{

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

	class LITHE_API Window
	{
	public:
		using EventCallback = std::function<void(Event&)>;

		Window() = delete;
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//virtual void SetEventCallback

		static std::unique_ptr<Window> Create(const WindowProperties& props = WindowProperties());

	};

}
