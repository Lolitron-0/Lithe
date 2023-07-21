#pragma once
#include "Lithe.hpp"

#define HOVER_FOCUS() do{if(ImGui::IsWindowHovered()) ImGui::SetWindowFocus();}while(0);

namespace Lithe
{
    class PanelBase
    {
    public:
        PanelBase() = default;
        PanelBase(const Ref<Scene>& scene) { this->SetTrackScene(m_Scene); }
        void SetTrackScene(const Ref<Scene>& scene) { m_Scene = scene; }

        virtual void OnImGuiDraw() = 0;
    protected:
        Ref<Scene> m_Scene;
    };
}