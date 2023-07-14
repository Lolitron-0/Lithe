#include "ltpch.h"
#include "MeshRendererComponent.hpp"

namespace Lithe
{

    MeshRendererComponent::MeshRendererComponent(const Ref<Ra::VertexArray>& vertexArray, const Ra::Material& material)
        :Material(material), VertexArray(vertexArray)
    {}

    MeshRendererComponent::MeshRendererComponent()
    {
        VertexArray = Ra::Renderer::Storage.CubeVertexArray;
    }

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