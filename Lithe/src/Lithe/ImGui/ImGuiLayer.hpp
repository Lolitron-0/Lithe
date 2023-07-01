#pragma once
#include "Lithe/Core/Layer.hpp"


namespace Lithe
{
    /// Layer that handles ImGui Begin/End frame logic
    class LITHE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiDraw() override;

        void Begin();
        void End();

    private:
        float m_Time{ 0.f };
    };
}
