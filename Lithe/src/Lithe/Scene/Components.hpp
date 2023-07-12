#pragma once
#include <glm/glm.hpp>
#include <RenderAbstraction.hpp>
#include "Components/Camera/CameraComponent.hpp"
#include "Components/TransformComponent.hpp"

namespace Lithe
{
    class MeshRendererComponent
    {
    public:
        Ra::Material Material;
        Ra::RendererAPI::DrawMode DrawingMode{ Ra::RendererAPI::DrawMode::Triangles };

        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent&) = default;
        MeshRendererComponent(const Ra::Material& material)
            :Material(material)
        {}
    };

    class PointLightComponent
    {
    public:
        Ra::PointLight Light;

        PointLightComponent() = default;
        PointLightComponent(const PointLightComponent&) = default;
        PointLightComponent(const Ra::PointLight& light)
            :Light(light)
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