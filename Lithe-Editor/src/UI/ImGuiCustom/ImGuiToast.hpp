#pragma once
#include <Lithe.hpp>

namespace Lithe {
    namespace ImGuiCustom {

        class ImGuiToast
        {
        public:
            enum class Severity
            {
                Message,
                Warning,
                Error,
            };
        public:
            ImGuiToast(const std::string message, Severity severity = Severity::Message, std::uint32_t lifetimeMs = 3000);
            void Render();

            bool Dead() const;
            ImVec2 GetSize() const;

            static const ImVec2 Padding;

        private:
            static ImVec4 SeverityToColor_(Severity severity);
        private:
            std::string m_Content;
            Stopwatch m_Clock;
            Severity m_Severity;
            std::uint32_t m_Lifetime;
        };
    }
}