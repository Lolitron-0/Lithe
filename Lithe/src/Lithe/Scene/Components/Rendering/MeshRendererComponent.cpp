#include "ltpch.h"
#include "MeshRendererComponent.hpp"

namespace Lithe
{

    MeshRendererComponent::MeshRendererComponent(const Ra::Material& material)
        :Material(material)
    {}

    void MeshRendererComponent::OnImGuiPropertiesDraw()
    {
        static const char* modes[] = { 
            "Points",
            "Triangles",
            "TriangleFan",
            "TriangleStrip",
            "Lines",
            "LineLoop",
            "LineStrip" 
        };

        ImGui::Combo("Drawing mode", (int*)&DrawingMode, modes, (int)Ra::RendererAPI::DrawMode::Count);

        //ImGui::ListBox("DrawModes", (int*)&DrawingMode, modes, (int)Ra::RendererAPI::DrawMode::Count);

    }

}