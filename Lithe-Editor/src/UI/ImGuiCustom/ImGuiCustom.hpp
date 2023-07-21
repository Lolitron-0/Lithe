#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <cstdint>
#include "ImGuiToast.hpp"

namespace Lithe
{
    namespace ImGuiCustom {

        void SetBounds(Vec2 bounds[2]);
        bool DrawToggleButton(const char* label, bool* val, ImVec2 size = { 0,0 });
        bool DrawToggleImageButton(ImTextureID texId, bool* val, ImVec2 size = { 20,20 });
        void DrawToggleList(const char* labels[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize = { 20.f,20.f }, ImVec2 offset = { 0,0 });
        void DrawToggleImageList(ImTextureID texIds[], bool vals[], int* chosen, std::size_t count, ImVec2 elSize = { 20.f,20.f }, ImVec2 offset = { 0,0 });
        void ShowToast(const std::string message, Log::Severity severity = Log::Severity::Trace, std::uint32_t lifetimeMs = 3000);
        void Render();

        extern Vec2 g_ContentAreaBounds[2];
    }
}
