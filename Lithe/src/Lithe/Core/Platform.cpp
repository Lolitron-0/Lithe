#include "ltpch.h"
#include "Platform/Windows/WindowsPlatform.hpp"

namespace Lithe 
{
#ifdef LT_PLATFORM_WINDOWS
    Lithe::Scope<Lithe::Platform> Platform::s_Instance = std::make_unique<WindowsPlatform>();
#else
#error "Only Windows is supported!"
#endif // LT_PLATFORM_WINDOWS


}