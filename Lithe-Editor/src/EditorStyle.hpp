#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <IconsFontAwesome5.h>

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
        static void SetupFonts();
        static void SetupDarkThemeColors();
        static ImFont* GetFont(FontStyle style);
    };

}