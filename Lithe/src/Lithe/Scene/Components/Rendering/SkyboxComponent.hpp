#pragma once
#include "Lithe/Scene/Components/ComponentBase.hpp"
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class SkyboxComponent : ComponentBase
    {
        MAKE_COMPONENT(SkyboxComponent)
    public:
        Ra::Skybox SkyboxObject;

        SkyboxComponent(const SkyboxComponent&) = default;
        SkyboxComponent(const Ra::Skybox& skybox);
        SkyboxComponent();

        void OnImGuiPropertiesDraw() override;
    };

}
