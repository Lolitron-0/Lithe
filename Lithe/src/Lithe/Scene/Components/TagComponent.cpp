#include "ltpch.h"
#include "TagComponent.hpp"
#include <imgui.h>

void Lithe::TagComponent::OnImGuiPropertiesDraw()
{
    memset(g_ScrapBuffer, 0, sizeof(g_ScrapBuffer));
    strcpy_s(g_ScrapBuffer, sizeof(g_ScrapBuffer), Tag.c_str());
    if (ImGui::InputText("Tag", g_ScrapBuffer, sizeof(g_ScrapBuffer)))
        Tag = std::string(g_ScrapBuffer);
}
