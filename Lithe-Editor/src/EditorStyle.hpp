#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <IconsFontAwesome5.h>
#include <cstdint>
#include <iostream>
#include "Lithe.hpp"

namespace Lithe
{
    enum class FontStyle
    {
        Regular = 0,
        Bold,
        Italic
    };

    class EditorStyle
    {
    public:
        static bool DrawToggleButton(const char* label, bool* val, ImVec2 size = {0,0});
        static bool DrawToggleImageButton(ImTextureID texId, bool* val, ImVec2 size = {20,20});
        static void DrawToggleList(const char* labels[],bool vals[], int* chosen, std::size_t count, ImVec2 elSize = { 20.f,20.f });
        static void DrawToggleImageList(ImTextureID texIds[], bool vals[],int* chosen, std::size_t count, ImVec2 elSize = {20.f,20.f});
        static void Init();
        static void SetupDarkThemeColors();
        static ImFont* GetFont(FontStyle style);

        static Ref<Ra::Texture> TranslateIcon;
        static Ref<Ra::Texture> RotateIcon;
        static Ref<Ra::Texture> ScaleIcon;
        static Ref<Ra::Texture> UniTransformIcon;
        static Ref<Ra::Texture> GlobalIcon;
        static Ref<Ra::Texture> GlobalIconMin;
    };

}