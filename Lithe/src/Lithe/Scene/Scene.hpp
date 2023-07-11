#pragma once
#include "EnTT/entt.hpp"
#include "Lithe/Core/Math.hpp"

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
        void OnViewportResize(std::uint32_t width, std::uint32_t height);

        friend class Entity;

    private:
        entt::registry m_Registry;
        Mat4 m_ViewProjection{ 1.f };
        Vec2 m_ViewportSize{ 0.f };
    };

}
