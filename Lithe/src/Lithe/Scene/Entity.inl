#include "Entity.hpp"
#include "Scene.hpp"

namespace Lithe
{
    template<class Component>
    Component& Entity::AddComponent()
    {
        return m_Scene.lock()->m_Registry.emplace<Component>(m_Handle);
    }

    template<class Component, class...Args>
    Component& Lithe::Entity::AddComponent(Args&&... args)
    {
        return m_Scene.lock()->m_Registry.emplace<Component>(m_Handle, std::forward<Args>(args)...);
    }

    template<class Component>
    Component& Entity::TryAddComponent()
    {
        return m_Scene.lock()->m_Registry.get_or_emplace<Component>(m_Handle);
    }

    template<class Component>
    Component& Entity::GetComponent() const
    {
        LITHE_ASSERT(this, "Attenpted to access deleted entity!");
        return m_Scene.lock()->m_Registry.get<Component>(m_Handle);
    }

    template<class Component>
    Component& Entity::GetComponent()
    {
        LITHE_ASSERT(this, "Attenpted to access deleted entity!");
        return m_Scene.lock()->m_Registry.get<Component>(m_Handle);
    }

    template<class ...Components>
    std::tuple<Components...>& Entity::GetComponents()
    {
        LITHE_ASSERT(this, "Attenpted to access deleted entity!");
        return m_Scene.lock()->m_Registry.get<Components...>(m_Handle);
    }

    template<class T>
    bool Entity::HasComponent()
    {
        return m_Scene.lock()->m_Registry.all_of<T>(m_Handle);
    }

    template<class T>
    void Entity::RemoveComponent()
    {
        m_Scene.lock()->m_Registry.remove<T>(m_Handle);
    }

}