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
        auto& group = m_Registry.group<TransformComponent>(entt::get<MeshRendererComponent>);

        for (auto& entity : group)
        {
            auto& [transform, mesh] = group.get<TransformComponent, MeshRendererComponent>(entity); 

            Ra::Renderer::DrawCube(transform, mesh.Shader, mesh.DrawingMode);
        }
    }

}