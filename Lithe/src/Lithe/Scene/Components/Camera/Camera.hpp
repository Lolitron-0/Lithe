#pragma once
#include "Lithe/Core/Math.hpp"

namespace Lithe
{
    class Camera
    {
    public:
        Mat4& GetProjection() { return m_Projection; }
        const Mat4& GetProjection() const { return m_Projection; }
    private:
        Mat4 m_Projection;
    };
}