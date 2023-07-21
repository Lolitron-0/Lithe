#pragma once
#include "Lithe.hpp"
#include "UI/Panels/Panels.hpp"
#include <ImGuizmo.h>

namespace Lithe
{

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void OnEvent(Event& event) override;
        bool OnKeyPressed(KeyPressedEvent& event);

        void OnImGuiDraw() override;

        void OnUpdate(const Lithe::Timestep& ts) override;

        void OnAttach() override;

    private:
        void DrawGizmo_();
        void DrawGizmoControls_();

        Ref<Scene> m_CurrentScene;
        Entity m_Model;
        Entity m_Sun;

        bool m_Loading{ true }; // @todo thread

        // Viewport
        Vec2 m_ViewportSize;
        Vec2 m_ViewportBounds[2];
        Entity m_EditorCamera;
        bool m_FlyMode{ false };
        Ref<EditorCameraController> m_CameraController;
        Ref<FlyCameraController> m_FlyCameraController;
        Ref<Ra::Framebuffer> m_Framebuffer;
        bool m_ViewportFocused{ true };

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;

        // Controls
        ImGuizmo::OPERATION m_CurrentGizmoOperation{ImGuizmo::OPERATION::UNIVERSAL};
        ImGuizmo::MODE m_CurrentGizmoMode{ImGuizmo::MODE::LOCAL};
    };

}
