#pragma once
#include "Lithe/Renderer/RenderingContext.hpp"
#include <GLFW/glfw3.h>

namespace Lithe
{
    class OpenGLContext final : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;

        GLFWwindow* m_WindowHandle;
    };

}
