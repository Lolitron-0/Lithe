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
        static bool DrawToggleButton(const char* label, bool* val, ImVec2 size = {0,0});
        static bool DrawToggleImageButton(ImTextureID texId, bool* val, ImVec2 size = {20,20});
        static void DrawToggleList(const char* labels[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize = { 20.f,20.f }, ImVec2 offset = {0,0});
        static void DrawToggleImageList(ImTextureID texIds[], bool vals[],int* chosen, std::size_t count, ImVec2 elSize = {20.f,20.f}, ImVec2 offset = { 0,0 });
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

}