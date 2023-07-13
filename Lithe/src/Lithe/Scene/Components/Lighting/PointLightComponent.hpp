#pragma once
#include "../ComponentBase.hpp"
#include <RenderAbstraction.hpp>
#include "Lithe/Core/Math.hpp"

namespace Lithe
{
    class PointLightComponent : public ComponentBase
    {
        MAKE_COMPONENT(PointLightComponent)

    public:
        Ra::PointLight Light;

        PointLightComponent() = default;
        PointLightComponent(const PointLightComponent&) = default;
        PointLightComponent(const Ra::PointLight& light);

        void OnImGuiPropertiesDraw() override;
    };
}