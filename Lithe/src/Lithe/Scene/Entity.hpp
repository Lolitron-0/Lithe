#pragma once
#include <EnTT/entt.hpp>

namespace Lithe
{
    class Scene;

    class Entity
    {
    public:
        Entity();
        Entity(entt::entity id, std::weak_ptr<Scene> parent);

        template<class Component>
        Component& AddComponent();

        template<class Component, class... Args>
        Component& AddComponent(Args&&... args);

        template<class Component>
        Component& TryAddComponent();

        template<class Component>
        Component& GetComponent() const;

        template<class Component>
        Component& GetComponent();

        template<class... Components>
        std::tuple<Components...>& GetComponents();

        template<class T>
        bool HasComponent();

        template<class T>
        void RemoveComponent();

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

#include "Entity.inl"