#pragma once
#include "Lithe/Core/Math.hpp"

namespace Lithe
{
    class TransformComponent
    {
    public:

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Mat4& transform)
            :Transform(transform)
        {}

        operator Mat4& () { return Transform; }
        operator const Mat4& () const { return Transform; }

    private:
        Vec3 m_Position;
        Vec3 m_Rotation;
        Vec3 m_Scale;
        Mat4 m_Transform{ 1.f };
    };

}