#include "ltpch.h"
#include "Camera.hpp"

namespace Lithe
{
    Camera::Camera()
        :m_Projection(MakePerspective(45.f, 16.f / 9.f))
    {}

    Camera::Camera(float fov, float aspectRatio, float nearPlane /*= 0.1f*/, float farPlane /*= 100.f*/)
    {
        this->SetPerspective(fov, aspectRatio, nearPlane, farPlane);
    }

    Camera::Camera(const Mat4& projection)
        :m_Projection(projection)
    {}

    void Camera::SetPerspective(float fov, float aspectRatio, float nearPlane /*= 0.1f*/, float farPlane /*= 100.f*/)
    {
        m_Projection = MakePerspective(fov, aspectRatio, nearPlane, farPlane);
    }

}