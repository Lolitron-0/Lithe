#pragma once
#include "Lithe/Scene/Components/ComponentBase.hpp"
#include <RenderAbstraction.hpp>

namespace Lithe
{
    class DirLightComponent : public ComponentBase
    {
        MAKE_COMPONENT(DirLightComponent)

    public:
        Ra::DirLight Light;

        DirLightComponent() = default;
        DirLightComponent(const DirLightComponent&) = default;
        DirLightComponent(const Ra::DirLight& light);

        void OnImGuiPropertiesDraw() override;
    };
}