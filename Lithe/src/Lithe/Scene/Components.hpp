#pragma once
#include <glm/glm.hpp>
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class TransformComponent
    {
        glm::mat4 Transform{1.f};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform)
            :Transform(transform)
        {}

        operator glm::mat4& () { return Transform; }
        operator const glm::mat4& () const { return Transform; }
    };

    class MeshRendererComponent
    {
        Ref<Ra::Shader> Shader;

        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent&) = default;
    };

}