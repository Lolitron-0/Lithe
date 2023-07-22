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
        PROFILER_SCOPE("Scene::OnUpdate()")
        {
            PROFILER_SCOPE("Scene: primary camera lookup");
            auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto& entity : group)
            {
                auto& [camera, transform] = group.get(entity);
                if (camera.Primary)
                {
                    m_ViewMatrix = glm::inverse(transform.GetMatrix());
                    m_ProjectionMatrix = camera.Camera->GetProjection();
                    m_PrimaryCamera = Entity{ entity, weak_from_this() };
                    break;
                }
            }
        }

        if (m_PrimaryCamera)
        {
            auto skyboxView = m_Registry.view<SkyboxComponent>();
            for (auto& entity : skyboxView)
            {
                Ra::Renderer::BeginScene(
                    m_ViewMatrix, m_ProjectionMatrix,
                    m_PrimaryCamera.GetComponent<TransformComponent>().GetPosition(),
                    skyboxView.get<SkyboxComponent>(entity).SkyboxObject);
                break;
            }


            {
                PROFILER_SCOPE("Scene: point light submission");
                auto pointLightGroup = m_Registry.group<PointLightComponent>(entt::get<TransformComponent>);
                for (auto& entitiy : pointLightGroup)
                {
                    auto& [pointLight, transform] = pointLightGroup.get(entitiy);
                    Ra::Renderer::SubmitLight(pointLight.Light, transform.GetPosition());
                }
            }

            {
                PROFILER_SCOPE("Scene: dir light submission");
                auto dirLightGroup = m_Registry.group<DirLightComponent>(entt::get<TransformComponent>);
                for (auto& entitiy : dirLightGroup)
                {
                    auto& [dirLight, transform] = dirLightGroup.get(entitiy);
                    dirLight.Light.Direction = transform.GetFront();
                    Ra::Renderer::SubmitLight(dirLight.Light);
                    Ra::Renderer::DrawVector(transform.GetPosition(), dirLight.Light.Direction);
                }
            }

            {
                PROFILER_SCOPE("Scene: rendering");
                auto& group = m_Registry.group<TransformComponent>(entt::get<MeshRendererComponent>);

                for (auto& entity : group)
                {
                    auto& [transform, mesh] = group.get<TransformComponent, MeshRendererComponent>(entity);

                    Ra::Renderer::Submit(mesh.MeshObject, { transform.GetMatrix(), transform.GetNormalMatrix() }, mesh.DrawingMode);
                }
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