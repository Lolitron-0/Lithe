#include "ltpch.h"
#include "SkyboxComponent.hpp"

namespace Lithe
{

    SkyboxComponent::SkyboxComponent(const Ra::Skybox& skybox)
        : SkyboxObject{ skybox }
    {

    }

    void SkyboxComponent::OnImGuiPropertiesDraw()
    {

    }

    SkyboxComponent::SkyboxComponent()
        : SkyboxObject{ "lol" }
    {

    }

}