#pragma once
#include "../ComponentBase.hpp"
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class MeshRendererComponent : public ComponentBase
    {
        MAKE_COMPONENT(MeshRendererComponent)
    public:
        Ref<Ra::Mesh> MeshObject;
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ref<Ra::Mesh>& mesh);
        MeshRendererComponent();

        void OnImGuiPropertiesDraw() override;

    };
    
}
