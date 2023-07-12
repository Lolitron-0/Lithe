#include "ltpch.h"
#include "Scene.hpp"
#include "Entity.hpp"
#include "Components.hpp"
#include "Lithe/Core/Timestep.hpp"

namespace Lithe
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity{ m_Registry.create(), weak_from_this() };
        entity.AddComponent<TransformComponent>(glm::mat4(1.f));
        auto& tagComponent = entity.AddComponent<TagComponent>();
        tagComponent.Tag = name.empty() ? "Unnamed entity" : name;
        return entity;
    }

    void Scene::OnUpdate(const Timestep& ts)
    {
        TransformComponent* activeCameraTransform = nullptr;
        {
            auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto& entity : group)
            {
                auto& [camera, transform] = group.get(entity);
                if (camera.Primary)
                {
                    activeCameraTransform = &transform;
                    m_ViewProjection = camera.Camera->GetProjection() * glm::inverse(transform.GetMatrix());
                    break;
                }
            }
        }

        Ra::Renderer::BeginScene(m_ViewProjection, activeCameraTransform->GetPosition());

        {
            auto pointLightGroup = m_Registry.group<PointLightComponent>(entt::get<TransformComponent>);
            for (auto& entitiy : pointLightGroup)
            {
                auto& [pointLight, transform] = pointLightGroup.get(entitiy);
                Ra::Renderer::SubmitPointLight(pointLight.Light, transform.GetPosition());
            }
        }


        auto& group = m_Registry.group<TransformComponent>(entt::get<MeshRendererComponent>);

        for (auto& entity : group)
        {
            auto& [transform, mesh] = group.get<TransformComponent, MeshRendererComponent>(entity);

            Ra::Renderer::DrawCube(transform, mesh.Material, mesh.DrawingMode);
        }

        Ra::Renderer::EndScene();
    }

    void Scene::OnViewportResize(std::uint32_t width, std::uint32_t height)
    {
        m_ViewportSize = { width, height };

        auto view = m_Registry.view<CameraComponent>();
        for (auto& entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.FixedAspectRatio)
                cameraComponent.Camera->SetAspectRatio(width / (float)height);
        }
    }

}