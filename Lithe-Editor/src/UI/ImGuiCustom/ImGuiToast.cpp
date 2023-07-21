#include "ImGuiToast.hpp"


namespace Lithe {
    namespace ImGuiCustom {

        ImGuiToast::ImGuiToast(const std::string message, Log::Severity severity /*= Log::Severity::Trace*/, std::uint32_t lifetimeMs /*= 3000*/)
            :m_Content{ message }, m_Lifetime{ lifetimeMs }, m_Severity{ severity }
        {

        }

        void ImGuiToast::Render()
        {
            ImGui::SetCursorPos(m_Position);
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

        bool ImGuiToast::IsPositioned() const
        {
            return !(m_Position.x == -1 && m_Position.y == -1);
        }

        ImVec2 ImGuiToast::GetPosition() const
        {
            return m_Position;
        }

        void ImGuiToast::SetPosition(ImVec2 position)
        {
            LITHE_ASSERT(!IsPositioned(), "Toast can only be positioned once!");
            m_Clock.Start();
            m_Position = position;
        }

        const ImVec2 ImGuiToast::Padding{10, 10};

        ImVec4 ImGuiToast::SeverityToColor_(Log::Severity severity)
        {
            switch (severity)
            {
            case Log::Severity::Trace:      return ImVec4{ 1, 1, 1, 1 };
            case Log::Severity::Debug:      return ImVec4{ 0, 0.561f, 0.4f, 1 };
            case Log::Severity::Info:       return ImVec4{ 0.204f, 0.941f, 0.545f, 1 };
            case Log::Severity::Warning:    return ImVec4{ 0.988f, 0.843f, 0.145f, 1 };
            case Log::Severity::Error:      return ImVec4{ 0.910f, 0.353f, 0.353f, 1 };
            case Log::Severity::Fatal:      return ImVec4{ 1, 0, 0, 1 };
            }
        }

    }
}