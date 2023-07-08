#pragma once
#include <glm/glm.hpp>
#include <RenderAbstraction.hpp>

namespace Lithe
{
    class MeshRendererComponent
    {
    public:
        Ref<Ra::Shader> Shader;
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ref<Ra::Shader>& shader)
            :Shader(shader)
        {}
    };

    class TagComponent
    {
    public:
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent& other) = default;
        TagComponent(const std::string& tag)
            :Tag(tag)
        {}
    };

}