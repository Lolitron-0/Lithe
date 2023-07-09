#pragma once
#include "Lithe/Core/Math.hpp"

namespace Lithe
{
    class Camera
    {
    public:
        Camera();
        Camera(const Mat4& projection);
        Camera(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.f);
        Camera(const Camera&) = default;

        Mat4& GetProjection() { return m_Projection; }
        const Mat4& GetProjection() const { return m_Projection; }

        void SetPerspective(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.f);
    private:
        Mat4 m_Projection;
    };
}