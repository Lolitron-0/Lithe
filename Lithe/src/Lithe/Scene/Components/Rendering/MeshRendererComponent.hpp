#pragma once
#include "../ComponentBase.hpp"
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class MeshRendererComponent : public ComponentBase
    {
        MAKE_COMPONENT(MeshRendererComponent)
    public:
        Ra::Mesh Mesh;
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ra::Mesh& mesh);
        MeshRendererComponent();

        void OnImGuiPropertiesDraw() override;

    };
    
}
