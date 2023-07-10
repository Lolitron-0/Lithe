#include "ltpch.h"
#include "PerspectiveCamera.hpp"

namespace Lithe
{
    PerspectiveCamera::PerspectiveCamera(float aspectRatio)
        :PerspectiveCamera(45.f, aspectRatio)
    {}

    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane /*= 0.1*/, float farPlane /*= 100.f*/)
        : Camera(aspectRatio)
    {
        m_Properties.Fov = fov;
        m_Properties.NearPlane = nearPlane;
        m_Properties.FarPlane = farPlane;
    }

    void PerspectiveCamera::RecalculateProjection_() const
    {
        m_Projection = MakePerspective(m_Properties.Fov, m_AspectRatio, m_Properties.NearPlane, m_Properties.FarPlane);
    }

    std::any PerspectiveCamera::GetCameraPropertiesImpl_() const
    {
        return std::any{m_Properties};
    }

    void PerspectiveCamera::SetCameraPropertiesImpl_(const std::any& val)
    {
        m_Properties = std::any_cast<PerspectiveCameraProperties>(val);
    }

}