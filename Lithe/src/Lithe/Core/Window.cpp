#include "ltpch.h"
#include "Window.hpp"
#include "Platform/WindowsWindow.hpp"

namespace Lithe
{
    Scope<Window> Window::Create(const WindowProperties& props)
    {
        #ifdef LT_PLATFORM_WINDOWS
            return std::make_unique<WindowsWindow>(props);
        #endif  
    }
}