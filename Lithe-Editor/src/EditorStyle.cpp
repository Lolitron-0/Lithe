#include "EditorStyle.hpp"
#include "Lithe.hpp"

namespace Lithe
{
    inline ImVec4 ToImGuiVec(const Vec4& v) { return ImVec4{ v.r,v.g,v.b,v.a }; }
    inline Vec4 ToVec(const ImVec4& v) { return Vec4{ v.x,v.y,v.z,v.w }; }
    inline Vec4 Desaturate(const Vec4& v, float value)
    {
        float i = (v.r + v.g + v.b) / 3;
        auto dr = i - v.r;
        auto dg = i - v.g;
        auto db = i - v.b;
        return {v.r + dr*value, v.g + dg * value, v.b + db * value, v.a};
    }
    inline Vec4 Lightness(const Vec4& v, float delta)
    {
        return v + Vec4{delta, delta, delta, 1};
    }

    void EditorStyle::SetupFonts()
    {
        ImGuiIO& io = ImGui::GetIO();
        float baseFontSize = 18.0f;
        float iconFontSize = baseFontSize * 2.0f / 3.0f;

        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.GlyphMinAdvanceX = iconFontSize;
        io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/Raleway/Raleway-Regular.ttf", baseFontSize);
        io.Fonts->AddFontFromFileTTF("assets/fonts/" FONT_ICON_FILE_NAME_FAS, iconFontSize, &icons_config, icons_ranges);
        io.Fonts->AddFontFromFileTTF("assets/fonts/Raleway/Raleway-ExtraBold.ttf", baseFontSize);
        io.Fonts->AddFontFromFileTTF("assets/fonts/Raleway/Raleway-Italic.ttf", baseFontSize);
    }

    void EditorStyle::SetupDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        Vec4 baseColor{ 0.3f, 0.15f, 0.3f, 1.f };

        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.09f, 0.1f, 1.f };

        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.19f, 0.2f, 1.f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.29f, 0.3f, 1.f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.095f, 0.08f, 0.095f, 1.f };

        colors[ImGuiCol_Tab] = ToImGuiVec(Lightness(baseColor, -.1f));
        colors[ImGuiCol_TabHovered] = ToImGuiVec(Lightness(ToVec(colors[ImGuiCol_Tab]), -.08f));
        colors[ImGuiCol_TabActive] = ImVec4{ 0.095f, 0.08f, 0.095f, 1.f };
        colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
        colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];

        colors[ImGuiCol_TitleBg] = ToImGuiVec(Lightness(Desaturate(baseColor, .4f), -.1f));
        colors[ImGuiCol_TitleBgActive] = ToImGuiVec(Lightness(ToVec(colors[ImGuiCol_TitleBg]), .05f));
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.095f, 0.05f, 0.095f, 1.f };

        colors[ImGuiCol_Button] = colors[ImGuiCol_TitleBg];
        colors[ImGuiCol_ButtonHovered] = colors[ImGuiCol_TitleBgActive];
        colors[ImGuiCol_ButtonActive] = colors[ImGuiCol_TitleBgCollapsed];

        colors[ImGuiCol_FrameBg] = colors[ImGuiCol_Button];
        colors[ImGuiCol_FrameBgHovered] = colors[ImGuiCol_ButtonHovered];
        colors[ImGuiCol_FrameBgActive] = colors[ImGuiCol_ButtonActive];
    }

    ImFont* EditorStyle::GetFont(FontStyle style)
    {
        ImGuiIO& io = ImGui::GetIO();
        return io.Fonts->Fonts[(int)style];
    }

}