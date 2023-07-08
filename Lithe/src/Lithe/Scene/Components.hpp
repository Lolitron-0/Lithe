#pragma once
#include <glm/glm.hpp>
#include <RenderAbstraction.hpp>

namespace Lithe
{

    class TransformComponent
    {
    public:
        glm::mat4 Transform{ 1.f };

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

    class CameraComponent
    {
    public:
        CameraComponent(const glm::mat4& proj)
            :m_Projection(proj)
        {}
        CameraComponent(float fov, float aspectRatio)
        CameraComponent(const CameraComponent& other) = default;
        
    private:
        glm::mat4 m_Projection;
    };

}