#pragma once
#include "Lithe.hpp"
#include "Panels/Panels.hpp"

namespace Lithe
{

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void OnEvent(Event& event) override;

        void OnImGuiDraw() override;

        void OnUpdate(const Lithe::Timestep& ts) override;

        void OnAttach() override;

    private:
        Ref<Ra::Texture> m_Texture;
        Ref<Ra::Framebuffer> m_Framebuffer;
        Ref<RMBCaptureFlyCameraController> m_CameraController;
        Ref<Scene> m_CurrentScene;
        Entity m_Cube;
        Entity m_Lamp;
        Ra::Material m_Material;
        Entity m_EditorCamera;

        glm::vec2 m_ViewportSize;

        bool m_ViewportFocused{ true };

        // Panels
        SceneHierarchyPanel m_SceneHierarchyPanel;

    };

}
