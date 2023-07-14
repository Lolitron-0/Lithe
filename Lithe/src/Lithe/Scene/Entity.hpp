#pragma once
#include <EnTT/entt.hpp>
#include "Scene.hpp"

namespace Lithe
{
    class Entity
    {
    public:
        Entity();
        Entity(entt::entity id, std::weak_ptr<Scene> parent);

        template<class Component>
        Component& AddComponent()
        {
            return m_Scene.lock()->m_Registry.emplace<Component>(m_Handle);
        }

        template<class Component, class... Args>
        Component& AddComponent(Args&&... args)
        {
            return m_Scene.lock()->m_Registry.emplace<Component>(m_Handle, std::forward<Args>(args)...);
        }

        template<class Component>
        Component& TryAddComponent()
        {
            return m_Scene.lock()->m_Registry.get_or_emplace<Component>(m_Handle);
        }

        template<class Component>
        Component& GetComponent() const
        {
            LITHE_ASSERT(this, "Attenpted to access deleted entity!");
            return m_Scene.lock()->m_Registry.get<Component>(m_Handle);
        }

        template<class Component>
        Component& GetComponent()
        {
            LITHE_ASSERT(this, "Attenpted to access deleted entity!");
            return m_Scene.lock()->m_Registry.get<Component>(m_Handle);
        }

        template<class... Components>
        std::tuple<Components...>& GetComponents()
        {
            LITHE_ASSERT(this, "Attenpted to access deleted entity!");
            return m_Scene.lock()->m_Registry.get<Components...>(m_Handle);
        }

        template<class T>
        bool HasComponent()
        {
            return m_Scene.lock()->m_Registry.all_of<T>(m_Handle);
        }

        template<class T>
        void RemoveComponent()
        {
            m_Scene.lock()->m_Registry.remove<T>(m_Handle);
        }

        operator bool() const { return m_Handle != entt::null; }
        operator std::uint32_t() const { return (std::uint32_t)m_Handle; }
        operator entt::entity() const { return m_Handle; }

        bool operator==(const Entity& other) const;
        bool operator!=(const Entity& other) const;

    private:
        entt::entity m_Handle{ entt::null };
        std::weak_ptr<Scene> m_Scene;
    };

}
