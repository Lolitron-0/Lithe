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
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ra::Material& material);

        void OnImGuiPropertiesDraw() override;

    };
    
}
