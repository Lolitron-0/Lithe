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
                    ImGui::PushID(T::GetComponentName());
                    ImGui::Columns(2);

                    auto deleteIcon = ICON_FA_TRASH;
                    float buttonWidth{ ImGui::CalcTextSize(deleteIcon).x + GImGui->Style.FramePadding.y * 2.f };
                    ImVec2 buttonSize{ buttonWidth, ImGui::CalcTextSize(deleteIcon).y + GImGui->Style.FramePadding.y * 2.f };

                    ImGui::SetColumnWidth(0, ImGui::GetWindowContentRegionMax().x - buttonSize.x * 1.3f);
                    ImGui::SeparatorText(T::GetComponentName());

                    ImGui::NextColumn();

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.35f, 0.4f, 1 });
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.55f, 0.5f, 1 });
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.25f, 0.27f, 1 });

                    if (ImGui::Button(deleteIcon, buttonSize))
                        removedComponent = true;
                    ImGui::PopStyleColor(3);

                    ImGui::Columns(1);
                    ImGui::PopID();
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