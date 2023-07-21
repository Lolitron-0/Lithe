#pragma once
#include <Lithe.hpp>

namespace Lithe {
    namespace ImGuiCustom {

        class ImGuiToast
        {
        public:
            ImGuiToast(const std::string message, Log::Severity severity = Log::Severity::Trace, std::uint32_t lifetimeMs = 3000);
            void Render();

            bool Dead() const;
            ImVec2 GetSize() const;

            /// Returns true if toast position has already been set
            bool IsPositioned() const;
            ImVec2 GetPosition() const;
            void SetPosition(ImVec2 position);

            static const ImVec2 Padding;

        private:
            static ImVec4 SeverityToColor_(Log::Severity severity);
        private:
            std::string m_Content;
            Stopwatch m_Clock;
            Log::Severity m_Severity;
            std::uint32_t m_Lifetime;
            ImVec2 m_Position{ -1, -1 };
        };
    }
}