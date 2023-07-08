#pragma once
#include "Camera.hpp"

namespace Lithe
{
    class CameraComponent
    {
    public:
        Lithe::Camera Camera;

        CameraComponent()
        {}
        CameraComponent(float fov, float aspectRatio);
        CameraComponent(const CameraComponent& other) = default;
    };

}