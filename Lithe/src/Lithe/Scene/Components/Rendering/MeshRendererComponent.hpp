#pragma once
#include "../ComponentBase.hpp"
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class MeshRendererComponent : public ComponentBase
    {
        MAKE_COMPONENT(MeshRendererComponent)
    public:
        Ra::Material Material;
        Ref<Ra::VertexArray> VertexArray;
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent();
        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ref<Ra::VertexArray>& vertexArray, const Ra::Material& material);

        void OnImGuiPropertiesDraw() override;

    };
    
}
