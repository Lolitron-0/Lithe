#pragma once
#include "Lithe/Core/Platform.hpp"
#include "GLFW/glfw3.h"

namespace Lithe
{
    class WindowsPlatform : public Platform
    {
    protected:
        double GetTimeImpl() override
        {
            return glfwGetTime();
        }

    };
}
