#include "ltpch.h"
#include "PointLightComponent.hpp"

namespace Lithe
{

    PointLightComponent::PointLightComponent(const Ra::PointLight& light) 
        :Light{ light }
    {}

    void PointLightComponent::OnImGuiPropertiesDraw()
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(Light.Color));
        ImGuiSliderFlags flags = ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_Logarithmic;
        ImGui::SliderFloat("Intensity", &Light.Intensity, 0.1f, 100.f, "%.3f", flags);
    }

}