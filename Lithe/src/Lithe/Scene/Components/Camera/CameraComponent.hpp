#pragma once
#include "Camera.hpp"
#include "../ComponentBase.hpp"

namespace Lithe
{
    class CameraComponent : public ComponentBase
    {
        MAKE_COMPONENT(CameraComponent)

    public:
        Ref<Lithe::Camera> Camera;
        bool Primary;
        bool FixedAspectRatio{ false };

        CameraComponent(const Ref<Lithe::Camera>& camera, bool primary)
            :Primary(primary), Camera(camera)
        {}
        CameraComponent(const CameraComponent& other) = default;

        void OnImGuiPropertiesDraw() override
        {
            throw std::logic_error("The method or operation is not implemented.");
        }

    };

}