#pragma once
#include "Camera.hpp"

namespace Lithe
{
    class CameraComponent
    {
    public:
        Lithe::Camera Camera;
        bool Primary;

        CameraComponent(bool primary)
            :Primary(primary)
        {}
        CameraComponent(float fov, float aspectRatio, bool primary)
            :Camera{ fov, aspectRatio }, Primary(primary)
        {}
        CameraComponent(const CameraComponent& other) = default;
    };

}