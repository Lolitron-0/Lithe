#include "EditorStyle.hpp"
#include "Lithe.hpp"
#include <ImGuizmo.h>

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
        return { v.r + dr * value, v.g + dg * value, v.b + db * value, v.a };
    }
    inline Vec4 Lightness(const Vec4& v, float delta)
    {
        return v + Vec4{delta, delta, delta, 1};
    }
    inline ImVec4 Lightness(const ImVec4& v, float delta)
    {
        return ImVec4{ v.x + delta, v.y + delta,v.z + delta, v.w };
    }

    bool EditorStyle::DrawToggleButton(const char* label, bool* val, ImVec2 size)
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

    bool EditorStyle::DrawToggleImageButton(ImTextureID texId, bool* val, ImVec2 size)
    {
        ImGui::PushID(texId);
        bool ret{ false };
        auto& colors = ImGui::GetStyle().Colors;
        if (*val)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(145, 75, 145, 255));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(171, 101, 171, 255));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(171, 101, 171, 255));
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

    void EditorStyle::DrawToggleList(const char* labels[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize)
    {
        for (std::size_t i{0}; i < count; i++)
        {
            if (DrawToggleButton(labels[i], &vals[i]) && !vals[i])
                vals[i] = true;
            if (vals[i])
            {
                *chosen = (int)i;
                for (std::size_t j{0}; j < count; j++)
                    if (j != i)
                        vals[j] = false;
            }
        }
    }

    void EditorStyle::DrawToggleImageList(ImTextureID texIds[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize /*= {20,20}*/)
    {
        for (std::size_t i{0}; i < count; i++)
        {
            if (DrawToggleImageButton(texIds[i], &vals[i], elSize))
            {
                vals[i] = true;
                if (vals[i])
                {
                    *chosen = (int)i;
                    for (std::size_t j{0}; j < count; j++)
                        if (j != i)
                            vals[j] = false;
                }
            }
            //ImGui::SameLine();
        }
    }

    void EditorStyle::Init()
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

        TranslateIcon = Ra::Texture::Create("assets/icons/translate70x70.png");
        RotateIcon = Ra::Texture::Create("assets/icons/rotate70x70.png");
        ScaleIcon = Ra::Texture::Create("assets/icons/scale70x70.png");
        UniTransformIcon = Ra::Texture::Create("assets/icons/unitransform70x70.png");
        GlobalIcon = Ra::Texture::Create("assets/icons/global.png");
        GlobalIconMin = Ra::Texture::Create("assets/icons/global70x70.png");

        auto& imguizmoStyle = ImGuizmo::GetStyle();
        imguizmoStyle.TranslationLineThickness = 5.f;
        imguizmoStyle.TranslationLineArrowSize = 8.f;
        imguizmoStyle.RotationLineThickness = 7.f;
        imguizmoStyle.ScaleLineThickness = 5.f;
        imguizmoStyle.ScaleLineCircleSize = 8.f;

        auto& imguizmoColors = imguizmoStyle.Colors;
        imguizmoColors[ImGuizmo::DIRECTION_X] =             ImVec4{ 0.800f, 0.227f, 0.149f, 1.f };
        imguizmoColors[ImGuizmo::DIRECTION_Y] =             ImVec4{ 0.149f, 0.769f, 0.294f, 1.f };
        imguizmoColors[ImGuizmo::DIRECTION_Z] =             ImVec4{ 0.153f, 0.455f, 0.769f, 1.f };
        imguizmoColors[ImGuizmo::PLANE_X] =                 ImVec4{ 0.800f, 0.227f, 0.149f, 0.380f };
        imguizmoColors[ImGuizmo::PLANE_Y] =                 ImVec4{ 0.149f, 0.769f, 0.294f, 0.380f };
        imguizmoColors[ImGuizmo::PLANE_Z] =                 ImVec4{ 0.153f, 0.455f, 0.769f, 0.380f };
        imguizmoColors[ImGuizmo::SELECTION] =               ImVec4{ 0.569f, 0.294f, 0.569f, 0.500f };
        imguizmoColors[ImGuizmo::ROTATION_USING_BORDER] =   ImVec4{ 0.569f, 0.294f, 0.569f, 1.000f };
        imguizmoColors[ImGuizmo::ROTATION_USING_FILL] =     ImVec4{ 0.569f, 0.294f, 0.569f, 0.500f };

    }

    void EditorStyle::SetupDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        Vec4 baseColor{ 0.36f, 0.17f, 0.36f, 1.f };

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

    Ra::Ref<Ra::Texture> EditorStyle::TranslateIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorStyle::RotateIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorStyle::ScaleIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorStyle::UniTransformIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorStyle::GlobalIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorStyle::GlobalIconMin = nullptr;
}