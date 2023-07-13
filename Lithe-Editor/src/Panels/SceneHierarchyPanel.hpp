#pragma once
#include "PanelBase.hpp"

namespace Lithe
{
    class SceneHierarchyPanel : public PanelBase
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void OnImGuiDraw() override;

    private:
        void DrawEntityNode_(const Entity& entity);
        void DrawProperties_(Entity& entity);
    private:
        mutable Entity m_SelectedEntity;
    };
}