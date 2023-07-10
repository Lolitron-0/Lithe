#include "ltpch.h"
#include "Camera.hpp"

namespace Lithe
{
    Camera::Camera(float aspectRatio)
        :m_Projection(1.f), m_AspectRatio(aspectRatio)
    {}

    Camera::Camera(const Mat4& projection)
        :m_Projection(projection)
    {}

    Lithe::Mat4& Camera::GetProjection()
    {
        if (m_ShouldRecalculateProjection)
        {
            RecalculateProjection_();
            m_ShouldRecalculateProjection = false;
        }
        return m_Projection;
    }

    const Lithe::Mat4& Camera::GetProjection() const
    {
        if (m_ShouldRecalculateProjection)
        {
            RecalculateProjection_();
            m_ShouldRecalculateProjection = false;
        }
        return m_Projection;
    }

    void Camera::SetAspectRatio(float ratio)
    {
        m_AspectRatio = ratio;
        m_ShouldRecalculateProjection = true;
    }

}