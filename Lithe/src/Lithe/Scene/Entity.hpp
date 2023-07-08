#pragma once
#include <EnTT/entt.hpp>

namespace Lithe
{
    class Scene;

    class Entity
    {
    public:
        Entity() = default;
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
        Component& GetComponent()
        {
            return m_Scene.lock()->m_Registry.get<Component>(m_Handle);
        }

        template<class... Components>
        std::tuple<Components...>& GetComponents()
        {
            return m_Scene.lock()->m_Registry.get<Components...>(m_Handle);
        }

        template<class T>
        bool HasComponent()
        {
            return m_Scene.lock()->m_Registry.has<T>();
        }

        template<class T>
        void RemoveComponent()
        {
            m_Scene.lock()->m_Registry.remove<T>();
        }

        operator bool() const { return m_Handle != entt::null; }

    private:
        entt::entity m_Handle{ entt::null };
        std::weak_ptr<Scene> m_Scene;
    };

}
