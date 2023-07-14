#pragma once
#include "Camera.hpp"
#include "PerspectiveCamera.hpp"
#include "../ComponentBase.hpp"

namespace Lithe
{
    class CameraComponent : public ComponentBase
    {
        MAKE_COMPONENT(CameraComponent)

    public:
        Ref<Lithe::Camera> Camera;
        bool Primary{ false };
        bool FixedAspectRatio{ false };

        CameraComponent()
            :Camera(MakeRef<Lithe::PerspectiveCamera>())
        {}
        CameraComponent(const Ref<Lithe::Camera>& camera, bool primary)
            :Primary(primary), Camera(camera)
        {}
        CameraComponent(const CameraComponent& other) = default;

        void OnImGuiPropertiesDraw() override
        {

        }

    };

}