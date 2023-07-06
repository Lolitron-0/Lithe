#include "ltpch.h"
#include "Entity.hpp"


namespace Lithe
{
    Entity::Entity(entt::entity id, std::weak_ptr<Scene> parent)
        :m_Handle(id), m_Scene(parent)
    {
    }
}