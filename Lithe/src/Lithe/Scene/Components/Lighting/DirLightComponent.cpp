#include "ltpch.h"
#include "DirLightComponent.hpp"

namespace Lithe
{

    DirLightComponent::DirLightComponent(const Ra::DirLight& light)
        :Light{ light }
    {

    }

    void DirLightComponent::OnImGuiPropertiesDraw()
    {
        ImGui::ColorEdit3("Color", glm::value_ptr(Light.Color));
        ImGuiSliderFlags flags = ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_Logarithmic;
        ImGui::SliderFloat("Intensity", &Light.Intensity, 0.1f, 100.f, "%.3f", flags);
    }

}