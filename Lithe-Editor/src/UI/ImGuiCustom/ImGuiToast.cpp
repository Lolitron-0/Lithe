#include "ImGuiToast.hpp"


namespace Lithe {
    namespace ImGuiCustom {

        ImGuiToast::ImGuiToast(const std::string message, Severity severity /*= Severity::Message*/, std::uint32_t lifetimeMs /*= 3000*/)
            :m_Content{ message }, m_Lifetime{ lifetimeMs }, m_Severity{ severity }
        {

        }

        void ImGuiToast::Render()
        {
            ImGui::TextColored(SeverityToColor_(m_Severity), m_Content.c_str());
        }

        bool ImGuiToast::Dead() const
        {
            return m_Clock.Elapsed<std::chrono::milliseconds>() > m_Lifetime;
        }

        ImVec2 ImGuiToast::GetSize() const
        {
            auto textSize = ImGui::CalcTextSize(m_Content.c_str());
            return {
                textSize.x + ImGui::GetStyle().FramePadding.x,
                textSize.y + ImGui::GetStyle().FramePadding.y
            };
        }

        const ImVec2 ImGuiToast::Padding{10, 10};

        ImVec4 ImGuiToast::SeverityToColor_(Severity severity)
        {
            switch (severity)
            {
            case Lithe::ImGuiCustom::ImGuiToast::Severity::Message:     return ImVec4{1, 1, 1, 1};
            case Lithe::ImGuiCustom::ImGuiToast::Severity::Warning:     return ImVec4{ 0.988f, 0.843f, 0.145f, 1 };
            case Lithe::ImGuiCustom::ImGuiToast::Severity::Error:       return ImVec4{ 0.910f, 0.353f, 0.353f, 1 };
            }
        }

    }
}