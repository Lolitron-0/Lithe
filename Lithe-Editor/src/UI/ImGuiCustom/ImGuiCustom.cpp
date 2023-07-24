#include "ImGuiCustom.hpp"
#include "EditorConfig.hpp"

namespace Lithe {
    namespace ImGuiCustom {

        Vec2 g_ContentAreaBounds[2];

        void SetBounds(Vec2 bounds[2])
        {
            g_ContentAreaBounds[0] = bounds[0];
            g_ContentAreaBounds[1] = bounds[1];
        }

        bool DrawToggleButton(const char* label, bool* val, ImVec2 size)
        {
            bool ret{ false };
            auto& colors = ImGui::GetStyle().Colors;
            if (*val)
            {
                ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(145, 75, 145, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(171, 101, 171, 255));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(171, 101, 171, 255));
                if (ImGui::Button(label, size))
                {
                    *val = false;
                    ret = true;
                }
                ImGui::PopStyleColor(3);
            }
            else
            {

                ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[ImGuiCol_ButtonHovered]);
                if (ImGui::Button(label, size))
                {
                    *val = true;
                    ret = true;
                }
                ImGui::PopStyleColor();
            }
            return ret;
        }

        bool DrawToggleImageButton(ImTextureID texId, bool* val, ImVec2 size)
        {
            ImGui::PushID(texId);
            bool ret{ false };
            auto& colors = ImGui::GetStyle().Colors;
            if (*val)
            {
                //ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.569, 0.294, 0.569, 1.f });
                ImGui::PushStyleColor(ImGuiCol_Button, ToImGuiVec(GetHighlight()));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ToImGuiVec(Lightness(GetHighlight(), 0.1f)));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ToImGuiVec(Lightness(GetHighlight(), -0.15f)));
                if (ImGui::ImageButton(texId, size))
                {
                    *val = false;
                    ret = true;
                }
                ImGui::PopStyleColor(3);
            }
            else
            {

                ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[ImGuiCol_ButtonHovered]);
                if (ImGui::ImageButton(texId, size))
                {
                    *val = true;
                    ret = true;
                }
                ImGui::PopStyleColor();
            }
            ImGui::PopID();
            return ret;
        }

        void DrawToggleList(const char* labels[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize, ImVec2 offset)
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset.y);
            for (std::size_t j{0}; j < count; j++)
                vals[j] = false;
            vals[*chosen] = true;
            for (std::size_t i{0}; i < count; i++)
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset.x);
                if (DrawToggleButton(labels[i], &vals[i]) && !vals[i])
                    vals[i] = true;
                if (vals[i])
                {
                    vals[*chosen] = false;
                    *chosen = (int)i;
                }
            }
        }

        void DrawToggleImageList(ImTextureID texIds[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize /*= {20,20}*/, ImVec2 offset)
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offset.y);
            for (std::size_t j{0}; j < count; j++)
                vals[j] = false;
            vals[*chosen] = true;
            for (std::size_t i{0}; i < count; i++)
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset.x);
                if (DrawToggleImageButton(texIds[i], &vals[i], elSize))
                    vals[i] = true;
                if (vals[i])
                {
                    vals[*chosen] = false;
                    *chosen = (int)i;
                }
            }
        }

        std::vector<ImGuiToast> activeToasts;

        void ShowToast(const std::string message, Log::Severity severity /*= Log::Severity::Trace*/, std::uint32_t lifetimeMs /*= 3000*/)
        {
            activeToasts.emplace_back(message, severity, lifetimeMs);
        }

        void Render()
        {
            std::uint32_t i{ 0 };
            ImVec2 startPos = { g_ContentAreaBounds[0].x + ImGuiToast::Padding.x, (g_ContentAreaBounds[1].y - g_ContentAreaBounds[0].y) - ImGui::CalcTextSize("A").y - ImGuiToast::Padding.y };
            for (; i < activeToasts.size(); i++)
            {
                if (activeToasts[i].Dead())
                {
                    activeToasts.erase(activeToasts.begin() + i);
                    i--;
                    continue;
                }
                if (!activeToasts[i].IsPositioned())
                {
                    ImVec2 pos;
                    if (i != 0)
                        pos = activeToasts[i-1].GetPosition();
                    else
                        pos = startPos;
                    activeToasts[i].SetPosition({ pos.x, pos.y - activeToasts[i].GetSize().y});
                }
                activeToasts[i].Render();
            }
        }

    }
}