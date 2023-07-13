#include "ltpch.h"
#include "Entity.hpp"


namespace Lithe
{
    Entity::Entity(entt::entity id, std::weak_ptr<Scene> parent)
        :m_Handle(id), m_Scene(parent)
    {
    }

    Entity::Entity()
        :Entity(entt::null, {})
    {

    }

    bool Entity::operator==(const Entity& other) const
    {
        return m_Handle == other.m_Handle && m_Scene.lock() == other.m_Scene.lock();
    }

    bool Entity::operator!=(const Entity& other) const
    {
        return !operator==(other);
    }


}