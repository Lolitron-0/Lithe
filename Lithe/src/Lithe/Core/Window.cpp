#include "Window.hpp"
#include "Platform/WindowsWindow.hpp"

namespace Lithe
{

    std::unique_ptr<Window> Window::Create(const WindowProperties& props)
    {
        #ifdef LT_PLATFORM_WINDOWS
            return std::make_unique<WindowsWindow>(props);
        #endif  
    }
}