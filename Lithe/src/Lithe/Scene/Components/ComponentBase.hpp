#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <IconsFontAwesome5.h>
#include "ComponentList.hpp"

#define MAKE_COMPONENT(className)  public:\
        static constexpr const char* GetComponentName() { return #className; } \
        static inline bool Removable = true;\
    private: \
    static_assert(Contains<className, ComponentsList>::value);

namespace Lithe
{
    class Entity;

    template<class T>
    class DrawAddComponentsListPopupFunctor
    {
    public:
        static void Call(Entity& entity)
        {
            if (!entity.HasComponent<T>())
            {
                if (ImGui::MenuItem(T::GetComponentName()))
                {
                    entity.AddComponent<T>();
                    ImGui::CloseCurrentPopup();
                }
            }
        }
    };

    template<class T>
    class DrawComponentsFunctor
    {
    public:
        static void Call(Entity& entity)
        {
            ImGuiWindow* window = ImGui::GetCurrentWindow();
            bool removedComponent = false;
            if (entity.HasComponent<T>())
            {
                auto& comp = entity.GetComponent<T>();
                if (T::Removable)
                {
                    ImGui::Columns(2);

                    float buttonWidth{ ImGui::CalcTextSize(ICON_FA_TRASH).x + GImGui->Style.FramePadding.y * 2.f };
                    ImVec2 buttonSize{ buttonWidth, buttonWidth };

                    ImGui::SetColumnWidth(0, ImGui::GetWindowWidth() - buttonSize.x * 2.f);
                    ImGui::SeparatorText(T::GetComponentName());

                    ImGui::NextColumn();

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.35f, 0.4f, 1 });
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.55f, 0.5f, 1 });
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.25f, 0.27f, 1 });
                    if (ImGui::Button(ICON_FA_TRASH, buttonSize))
                        removedComponent = true;
                    ImGui::PopStyleColor(3);

                    ImGui::Columns(1);
                }
                else
                    ImGui::SeparatorText(T::GetComponentName());

                comp.OnImGuiPropertiesDraw();

                if (removedComponent)
                    entity.RemoveComponent<T>();
            }
        }
    };

    class ComponentBase
    {
    public:
        virtual void OnImGuiPropertiesDraw() = 0;
    };
}