#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <ImGuizmo.h>
#include <IconsFontAwesome5.h>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include "Lithe.hpp"

namespace Lithe
{
    enum class FontStyle : std::uint8_t
    {
        Regular = 0,
        Bold,
        Italic
    };

    enum class KeybindOperations
    {
        HoldGizmoSnap,
        GizmoModeTranslate,
        GizmoModeRotate,
        GizmoModeScale,
        GizmoModeUniversal,
        FlyModeToggle,
        Focus,
    };

    class EditorConfig
    {
    public:
        static void Init();
        static void SetupDarkThemeColors();
        static ImFont* GetFont(FontStyle style);
        static bool IsPressed(KeybindOperations operation);
        static float* GetGizmoSnap(ImGuizmo::OPERATION operation);
        static const Vec4 GetBaseColor();

        static Ref<Ra::Texture> TranslateIcon;
        static Ref<Ra::Texture> RotateIcon;
        static Ref<Ra::Texture> ScaleIcon;
        static Ref<Ra::Texture> UniTransformIcon;
        static Ref<Ra::Texture> GlobalIcon;
        static Ref<Ra::Texture> GlobalIconMin;
    private:
        static const std::unordered_map<KeybindOperations, std::vector<Keyboard::Key>> s_KeybindingsMap;
        static Vec4 s_BaseColor;
    };

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
    inline Vec4 GetHighlight()
    {
        return Desaturate(Lightness(EditorConfig::GetBaseColor(), .135f), -0.35f);
    }

}