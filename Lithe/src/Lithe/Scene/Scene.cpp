#include "ltpch.h"
#include "Scene.hpp"
#include "Entity.hpp"

namespace Lithe
{
    Entity Scene::CreateEntity()
    {
        return Entity{ m_Registry.create(), shared_from_this() };
    }
}