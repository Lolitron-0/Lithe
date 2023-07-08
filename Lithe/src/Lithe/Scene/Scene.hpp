#pragma once
#include "EnTT/entt.hpp"

namespace Lithe
{
    class Entity;
    class Timestep;

    class Scene : public std::enable_shared_from_this<Scene>
    {
    public:
        Scene() = default;

        Entity CreateEntity(const std::string& name = std::string{});
        void OnUpdate(const Timestep& ts);

        friend class Entity;

    private:
        entt::registry m_Registry;
    };

}
