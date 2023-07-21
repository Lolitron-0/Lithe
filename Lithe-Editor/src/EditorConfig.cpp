#include "EditorConfig.hpp"
#include "Lithe.hpp"

namespace Lithe
{
    void EditorConfig::Init()
    {

        // Theme
        SetupDarkThemeColors();

        // Fonts
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

        // ImGui
        auto& imguiStyle = ImGui::GetStyle();
        imguiStyle.FrameRounding = 7.f;
        imguiStyle.PopupRounding = 7.f;
        imguiStyle.ScrollbarRounding = 7.f;

        // Icons
        TranslateIcon = Ra::Texture::Create("assets/icons/translate70x70.png");
        RotateIcon = Ra::Texture::Create("assets/icons/rotate70x70.png");
        ScaleIcon = Ra::Texture::Create("assets/icons/scale70x70.png");
        UniTransformIcon = Ra::Texture::Create("assets/icons/unitransform70x70.png");
        GlobalIcon = Ra::Texture::Create("assets/icons/global.png");
        GlobalIconMin = Ra::Texture::Create("assets/icons/global70x70.png");

        // Gizmo
        auto& imguizmoStyle = ImGuizmo::GetStyle();
        imguizmoStyle.TranslationLineThickness = 5.f;
        imguizmoStyle.TranslationLineArrowSize = 8.f;
        imguizmoStyle.RotationLineThickness = 7.f;
        imguizmoStyle.ScaleLineThickness = 5.f;
        imguizmoStyle.ScaleLineCircleSize = 8.f;

        auto& imguizmoColors = imguizmoStyle.Colors;
        imguizmoColors[ImGuizmo::DIRECTION_X] = ImVec4{ 0.800f, 0.227f, 0.149f, 1.f };
        imguizmoColors[ImGuizmo::DIRECTION_Y] = ImVec4{ 0.149f, 0.769f, 0.294f, 1.f };
        imguizmoColors[ImGuizmo::DIRECTION_Z] = ImVec4{ 0.153f, 0.455f, 0.769f, 1.f };
        imguizmoColors[ImGuizmo::PLANE_X] = ImVec4{ 0.800f, 0.227f, 0.149f, 0.380f };
        imguizmoColors[ImGuizmo::PLANE_Y] = ImVec4{ 0.149f, 0.769f, 0.294f, 0.380f };
        imguizmoColors[ImGuizmo::PLANE_Z] = ImVec4{ 0.153f, 0.455f, 0.769f, 0.380f };
        imguizmoColors[ImGuizmo::SELECTION] = ImVec4{ 0.569f, 0.294f, 0.569f, 0.500f };
        imguizmoColors[ImGuizmo::ROTATION_USING_BORDER] = ImVec4{ 0.569f, 0.294f, 0.569f, 1.000f };
        imguizmoColors[ImGuizmo::ROTATION_USING_FILL] = ImVec4{ 0.569f, 0.294f, 0.569f, 0.500f };

    }

    void EditorConfig::SetupDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.09f, 0.1f, 1.f };

        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.19f, 0.2f, 1.f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.29f, 0.3f, 1.f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.095f, 0.08f, 0.095f, 1.f };

        colors[ImGuiCol_Tab] = ToImGuiVec(Lightness(s_BaseColor, -.1f));
        colors[ImGuiCol_TabHovered] = ToImGuiVec(Lightness(ToVec(colors[ImGuiCol_Tab]), -.08f));
        colors[ImGuiCol_TabActive] = ImVec4{ 0.095f, 0.08f, 0.095f, 1.f };
        colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
        colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_TabActive];

        colors[ImGuiCol_TitleBg] = ToImGuiVec(Lightness(Desaturate(s_BaseColor, .4f), -.1f));
        colors[ImGuiCol_TitleBgActive] = ToImGuiVec(Lightness(ToVec(colors[ImGuiCol_TitleBg]), .05f));
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.095f, 0.05f, 0.095f, 1.f };

        colors[ImGuiCol_Button] = colors[ImGuiCol_TitleBg];
        colors[ImGuiCol_ButtonHovered] = colors[ImGuiCol_TitleBgActive];
        colors[ImGuiCol_ButtonActive] = colors[ImGuiCol_TitleBgCollapsed];

        colors[ImGuiCol_FrameBg] = colors[ImGuiCol_Button];
        colors[ImGuiCol_FrameBgHovered] = colors[ImGuiCol_ButtonHovered];
        colors[ImGuiCol_FrameBgActive] = colors[ImGuiCol_ButtonActive];
    }

    ImFont* EditorConfig::GetFont(FontStyle style)
    {
        ImGuiIO& io = ImGui::GetIO();
        return io.Fonts->Fonts[(int)style];
    }

    bool EditorConfig::IsPressed(KeybindOperations operation)
    {
        auto keys = s_KeybindingsMap.at(operation);
        bool res = true;
        for (const auto& key : keys)
            res &= Keyboard::IsKeyPressed(key);
        return res;
    }

    float* EditorConfig::GetGizmoSnap(ImGuizmo::OPERATION operation)
    {
        switch (operation)
        {
        case ImGuizmo::TRANSLATE:
        case ImGuizmo::TRANSLATE_X:
        case ImGuizmo::TRANSLATE_Y:
        case ImGuizmo::TRANSLATE_Z:
        {
            static float translationSnap[] = { .25f, .25f, .25f };
            return translationSnap;
        }
        case ImGuizmo::ROTATE:
        case ImGuizmo::ROTATE_X:
        case ImGuizmo::ROTATE_Y:
        case ImGuizmo::ROTATE_Z:
        {
            static float rotationSnap[] = { 15.f, 15.f, 15.f };
            return rotationSnap;
        }
        case ImGuizmo::SCALE:
        case ImGuizmo::SCALE_X:
        case ImGuizmo::SCALE_Y:
        case ImGuizmo::SCALE_Z:
        {
            static float scaleSnap[] = { .25f, .25f, .25f };
            return scaleSnap;
        }
        case ImGuizmo::UNIVERSAL:
        {
            static float universalSnap[] = { 1.f, 1.f, 1.f };
            return universalSnap;
        }
        }
        return nullptr;
    }

    const Vec4 EditorConfig::GetBaseColor()
    {
        return s_BaseColor;
    }

    Ra::Ref<Ra::Texture> EditorConfig::TranslateIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorConfig::RotateIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorConfig::ScaleIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorConfig::UniTransformIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorConfig::GlobalIcon = nullptr;
    Ra::Ref<Ra::Texture> EditorConfig::GlobalIconMin = nullptr;

    const std::unordered_map<Lithe::KeybindOperations, std::vector<Lithe::Keyboard::Key>> EditorConfig::s_KeybindingsMap =
    {
        {KeybindOperations::HoldGizmoSnap,          {Keyboard::Key::J }},
        { KeybindOperations::GizmoModeTranslate,    {Keyboard::Key::W }},
        { KeybindOperations::GizmoModeRotate,       {Keyboard::Key::E }},
        { KeybindOperations::GizmoModeScale,        {Keyboard::Key::R }},
        { KeybindOperations::GizmoModeUniversal,    {Keyboard::Key::T }},
        { KeybindOperations::Focus,                 {Keyboard::Key::F }},
        { KeybindOperations::FlyModeToggle,         {Keyboard::Key::F, Keyboard::Key::LeftShift, Keyboard::Key::LeftControl }},
    };

    Vec4 EditorConfig::s_BaseColor{0.36f, 0.17f, 0.36f, 1.f};

}