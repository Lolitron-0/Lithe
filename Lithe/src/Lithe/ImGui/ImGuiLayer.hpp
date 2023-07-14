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

        void OnEvent(Event& event) override;

        void Begin();
        void End();

        void BlockEvents(bool block);

    private:
        float m_Time{ 0.f };
        bool m_BlockEvents{ false };
    };
}
