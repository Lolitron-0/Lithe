#pragma once
#include "Camera.hpp"

namespace Lithe
{
    class CameraComponent
    {
    public:
        Ref<Lithe::Camera> Camera;
        bool Primary;
        bool FixedAspectRatio{ false };

        CameraComponent(const Ref<Lithe::Camera>& camera, bool primary)
            :Primary(primary), Camera(camera)
        {}
        CameraComponent(const CameraComponent& other) = default;
    };

}