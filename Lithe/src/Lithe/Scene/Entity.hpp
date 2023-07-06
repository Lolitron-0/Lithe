#pragma once
#include <EnTT/entt.hpp>

namespace Lithe
{
    class Scene;

    class Entity
    {
    public:
        Entity(entt::entity id, std::weak_ptr<Scene> parent);

        template<class Component>
        Component& AddComponent()
        {
            return m_Scene.lock()->m_Registry.emplace<Component>(m_Handle);
        }

        template<class... Components>
        std::tuple<Components...>& GetComponent() 
        {
            return m_Scene.lock()->m_Registry.get<Components...>();
        }

    private:
        entt::entity m_Handle;
        std::weak_ptr<Scene> m_Scene;
    };

}
