#include "ltpch.h"
#include "RenderingContext.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"

namespace Lithe
{
    Scope<RenderingContext> RenderingContext::Create(std::any windowHandle)
    {
        if (1) // TODO: check rendering api
            return std::make_unique<OpenGLContext>(std::any_cast<GLFWwindow*>(windowHandle));
    }
}