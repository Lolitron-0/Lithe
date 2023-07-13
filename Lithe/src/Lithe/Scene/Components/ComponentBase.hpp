#pragma once
#include <imgui.h>
#include "ComponentList.hpp"

#define MAKE_COMPONENT(className)  public:\
        static constexpr const char* GetComponentName() { return #className; } \
    private: \
    static_assert(Contains<className, ComponentsList>::value);

namespace Lithe
{
    class Entity;

    template<class T>
    class DrawComponentsFunctor
    {
    public:
        static void Call(Entity& entity)
        {
            if (entity.HasComponent<T>())
            {
                auto& comp = entity.GetComponent<T>();
                ImGui::SeparatorText(T::GetComponentName());
                comp.OnImGuiPropertiesDraw();
            }
        }
    };

    class ComponentBase
    {
    public:
        virtual void OnImGuiPropertiesDraw() = 0;
    };
}