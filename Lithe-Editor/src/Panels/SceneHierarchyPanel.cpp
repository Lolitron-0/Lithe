#include "SceneHierarchyPanel.hpp"
#include "Lithe/Scene/Components/ComponentList.hpp"

namespace Lithe
{

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& scene)
        :PanelBase(scene)
    {}

    void SceneHierarchyPanel::OnImGuiDraw()
    {
        ImGui::Begin("Scene hierarchy");

        m_Scene->m_Registry.each([this](const entt::entity entityHandle)
            {
                Entity entity{ entityHandle, m_Scene };
                DrawEntityNode_(entity);
            }
        );

        ImGui::End();

        ImGui::Begin("Properties");

        if (m_SelectedEntity)
            this->DrawProperties_(m_SelectedEntity);

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode_(const Entity& entity)
    {
        ImGuiTreeNodeFlags flags{ImGuiTreeNodeFlags_OpenOnArrow | (m_SelectedEntity == entity ? ImGuiTreeNodeFlags_Selected : 0)};
        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>((std::uintptr_t)(std::uint32_t)entity), flags, entity.GetComponent<TagComponent>().Tag.c_str());
        if (ImGui::IsItemClicked())
            m_SelectedEntity = entity;
        
        if (opened)
        {
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::DrawProperties_(Entity& entity)
    {
        ForEach<ComponentsList, DrawComponentsFunctor>::Iterate(entity);
    }

}