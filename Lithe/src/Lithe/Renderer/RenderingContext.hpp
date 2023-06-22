#pragma once
#include <any>

namespace Lithe
{
    class LITHE_API RenderingContext
    {
    public:
        virtual ~RenderingContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<RenderingContext> Create(std::any windowHandle);
    };
}