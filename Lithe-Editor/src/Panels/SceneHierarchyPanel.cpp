#include "SceneHierarchyPanel.hpp"
#include "Lithe/Scene/Components/ComponentList.hpp"
#include <imgui_internal.h>

namespace Lithe
{

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
        :PanelBase(scene)
    {}

    void SceneHierarchyPanel::OnImGuiDraw()
    {
        ImGui::Begin("Scene hierarchy");
        HOVER_FOCUS();
        m_Scene->m_Registry.each([this](const entt::entity entityHandle)
            {
                Entity entity{ entityHandle, m_Scene };
                DrawEntityNode_(entity);
            }
        );

        ImGuiPopupFlags flags = ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight;
        if (ImGui::BeginPopupContextWindow(nullptr, flags))
        {
            if (ImGui::MenuItem("Create empty entity"))
                m_Scene->CreateEntity("Empty entity");

            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Properties");
        HOVER_FOCUS();
        if (m_SelectedEntity)
            this->DrawProperties_(m_SelectedEntity);

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode_(const Entity& entity)
    {
        ImGuiTreeNodeFlags flags{ ImGuiTreeNodeFlags_OpenOnArrow | (m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0) };
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>((std::uintptr_t)(std::uint32_t)entity), flags, entity.GetComponent<TagComponent>().Tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectedEntity = entity;
        }

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Destroy entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            m_Scene->DestroyEntity(entity);
            m_SelectedEntity = {};
        }
    }

    void SceneHierarchyPanel::DrawProperties_(Entity& entity)
    {
        ForEach<ComponentsList, DrawComponentsFunctor>::Iterate(entity);

        ImGuiSeparatorFlags flags = ImGuiSeparatorFlags_Horizontal;
        ImGui::SeparatorEx(flags, 3);

        if (ImGui::Button(ICON_FA_PLUS "Add component", ImVec2{ ImGui::GetWindowContentRegionMax().x, GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f }))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            ForEach<ComponentsList, DrawAddComponentsListPopupFunctor>::Iterate(entity);
            ImGui::EndPopup();
        }
    }

}