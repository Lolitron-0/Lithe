#include "ltpch.h"
#include "MeshRendererComponent.hpp"

namespace Lithe
{

    MeshRendererComponent::MeshRendererComponent(const Ref<Ra::Mesh>& mesh)
        :MeshObject{ mesh }
    {}

    MeshRendererComponent::MeshRendererComponent()
    {
        MeshObject = Ra::Mesh::Create("assets/meshes/DefaultMesh.fbx");
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