#include "ltpch.h"
#include "Scene.hpp"
#include "Entity.hpp"
#include "Components/Components.hpp"
#include "Lithe/Core/Timestep.hpp"

namespace Lithe
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity{ m_Registry.create(), weak_from_this() };
        entity.AddComponent<TransformComponent>(glm::mat4(1.f));
        TransformComponent::Removable = false;

        auto& tagComponent = entity.AddComponent<TagComponent>();
        tagComponent.Tag = name.empty() ? "Unnamed entity" : name;
        TagComponent::Removable = false;

        return entity;
    }

    void Scene::DestroyEntity(const Entity& entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdate(const Timestep& ts)
    {
        {
            auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto& entity : group)
            {
                auto& [camera, transform] = group.get(entity);
                if (camera.Primary)
                {
                    m_ViewProjection = camera.Camera->GetProjection() * glm::inverse(transform.GetMatrix()); // splitted storage to avoid multiply+inverse several times
                    m_PrimaryCamera = Entity{ entity, weak_from_this() };
                    break;
                }
            }
        }

        if (m_PrimaryCamera)
        {
            Ra::Renderer::BeginScene(m_ViewProjection, m_PrimaryCamera.GetComponent<TransformComponent>().GetPosition());

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

                Ra::Renderer::Submit(mesh.VertexArray, {transform.GetMatrix(), transform.GetNormalMatrix()}, mesh.Material, mesh.DrawingMode);
            }

            Ra::Renderer::EndScene();
        }
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

    Entity Scene::GetSelectedEntity() const
    {
        return m_SelectedEntity;
    }

    Lithe::Entity Scene::GetPrimaryCameraEntity() const
    {
        return m_PrimaryCamera;
    }

}