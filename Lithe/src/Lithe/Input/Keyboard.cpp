#include "ltpch.h"
#include "Keyboard.hpp"

namespace Lithe
{
    const std::unordered_map<Keyboard::Key, std::string> Keyboard::s_KeyToStringMap
    {
         {Key::Unknown,           "Unknown"},
         {Key::Space,             "Space"},
         {Key::Apostrophe,        "Apostrophe"},
         {Key::Comma,             "Comma"},
         {Key::Minus,             "Minus"},
         {Key::Period,            "Period"},
         {Key::Slash,             "Slash"},
         {Key::Key0,              "Key0"},
         {Key::Key1,              "Key1"},
         {Key::Key2,              "Key2"},
         {Key::Key3,              "Key3"},
         {Key::Key4,              "Key4"},
         {Key::Key5,              "Key5"},
         {Key::Key6,              "Key6"},
         {Key::Key7,              "Key7"},
         {Key::Key8,              "Key8"},
         {Key::Key9,              "Key9"},
         {Key::Semicolon,         "Semicolon"},
         {Key::EQUAL,             "EQUAL"},
         {Key::A,                 "A"},
         {Key::B,                 "B"},
         {Key::C,                 "C"},
         {Key::D,                 "D"},
         {Key::E,                 "E"},
         {Key::F,                 "F"},
         {Key::G,                 "G"},
         {Key::H,                 "H"},
         {Key::I,                 "I"},
         {Key::J,                 "J"},
         {Key::K,                 "K"},
         {Key::L,                 "L"},
         {Key::M,                 "M"},
         {Key::N,                 "N"},
         {Key::O,                 "O"},
         {Key::P,                 "P"},
         {Key::Q,                 "Q"},
         {Key::R,                 "R"},
         {Key::S,                 "S"},
         {Key::T,                 "T"},
         {Key::U,                 "U"},
         {Key::V,                 "V"},
         {Key::W,                 "W"},
         {Key::X,                 "X"},
         {Key::Y,                 "Y"},
         {Key::Z,                 "Z"},
         {Key::LeftBracket,       "LeftBracket"},
         {Key::Backslash,         "Backslash"},
         {Key::RightBracket,      "RightBracket"},
         {Key::GraveAccent,       "GraveAccent"},
         {Key::World1,            "World1"},
         {Key::World2,            "World2"},
         {Key::Escape,            "Escape"},
         {Key::Enter,             "Enter"},
         {Key::Tab,               "Tab"},
         {Key::Backspace,         "Backspace"},
         {Key::Insert,            "Insert"},
         {Key::Delete,            "Delete"},
         {Key::Right,             "Right"},
         {Key::Left,              "Left"},
         {Key::Down,              "Down"},
         {Key::Up,                "Up"},
         {Key::PageUp,            "PageUp"},
         {Key::PageDown,          "PageDown"},
         {Key::Home,              "Home"},
         {Key::End,               "End"},
         {Key::CapsLock,          "CapsLock"},
         {Key::ScrollLock,        "ScrollLock"},
         {Key::NumLock,           "NumLock"},
         {Key::PrintScreen,       "PrintScreen"},
         {Key::Pause,             "Pause"},
         {Key::F1,                "F1"},
         {Key::F2,                "F2"},
         {Key::F3,                "F3"},
         {Key::F4,                "F4"},
         {Key::F5,                "F5"},
         {Key::F6,                "F6"},
         {Key::F7,                "F7"},
         {Key::F8,                "F8"},
         {Key::F9,                "F9"},
         {Key::F10,               "F10"},
         {Key::F11,               "F11"},
         {Key::F12,               "F12"},
         {Key::F13,               "F13"},
         {Key::F14,               "F14"},
         {Key::F15,               "F15"},
         {Key::F16,               "F16"},
         {Key::F17,               "F17"},
         {Key::F18,               "F18"},
         {Key::F19,               "F19"},
         {Key::F20,               "F20"},
         {Key::F21,               "F21"},
         {Key::F22,               "F22"},
         {Key::F23,               "F23"},
         {Key::F24,               "F24"},
         {Key::F25,               "F25"},
         {Key::Num0,              "Num0"},
         {Key::Num1,              "Num1"},
         {Key::Num2,              "Num2"},
         {Key::Num3,              "Num3"},
         {Key::Num4,              "Num4"},
         {Key::Num5,              "Num5"},
         {Key::Num6,              "Num6"},
         {Key::Num7,              "Num7"},
         {Key::Num8,              "Num8"},
         {Key::Num9,              "Num9"},
         {Key::NumDecimal,        "NumDecimal"},
         {Key::NumDivide,         "NumDivide"},
         {Key::NumMultiply,       "NumMultiply"},
         {Key::NumSubstract,      "NumSubstract"},
         {Key::NumAdd,            "NumAdd"},
         {Key::NumEnter,          "NumEnter"},
         {Key::NumEqual,          "NumEqual"},
         {Key::LeftShift,         "LeftShift"},
         {Key::LeftControl,       "LeftControl"},
         {Key::LeftAlt,           "LeftAlt"},
         {Key::LeftSuper,         "LeftSuper"},
         {Key::RightShift,        "RightShift"},
         {Key::RightControl,      "RightControl"},
         {Key::RightAlt,          "RightAlt"},
         {Key::RightSuper,        "RightSuper"},
         {Key::Menu,              "Menu"},
    };
    std::string Keyboard::KeyToString(Key key)
    {
        return s_KeyToStringMap.at(key);
    }
}