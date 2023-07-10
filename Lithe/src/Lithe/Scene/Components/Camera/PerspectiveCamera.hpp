#pragma once
#include "Camera.hpp"

namespace Lithe
{
    struct PerspectiveCameraProperties
    {
        float Fov;
        float NearPlane;
        float FarPlane;
    };

    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float aspectRatio);
        PerspectiveCamera(float fov, float aspectRatio, float nearPlane = 0.1, float farPlane = 100.f);
    private:
        void RecalculateProjection_() const override;
        std::any GetCameraPropertiesImpl_() const override;
        void SetCameraPropertiesImpl_(const std::any& val) override;

        PerspectiveCameraProperties m_Properties;
    };

}
