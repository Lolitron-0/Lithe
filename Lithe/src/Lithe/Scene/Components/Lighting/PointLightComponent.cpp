#include "ltpch.h"
#include "PointLightComponent.hpp"

namespace Lithe
{

    PointLightComponent::PointLightComponent(const Ra::PointLight& light) 
        :Light(light)
    {}

    void PointLightComponent::OnImGuiPropertiesDraw()
    {
        static float color[] = { 1,1,1 };
        if (ImGui::ColorEdit3("Color", color))
            Light.Color = { color[0], color[1], color[2] };
    }

}