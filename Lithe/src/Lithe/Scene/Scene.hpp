#pragma once
#include "EnTT/entt.hpp"

namespace Lithe
{
    class Entity;

    class Scene : public std::enable_shared_from_this<Scene>
    {
    public:
        Scene() = default;

        Entity CreateEntity();

        friend class Entity;

    private:
        entt::registry m_Registry;
    };

}
