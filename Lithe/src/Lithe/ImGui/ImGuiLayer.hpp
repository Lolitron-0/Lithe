#pragma once
#include "Lithe/Core/Layer.hpp"


namespace Lithe
{
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
