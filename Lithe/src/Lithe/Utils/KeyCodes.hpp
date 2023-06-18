#include "Lithe/Core/Base.hpp"
#include "Lithe/Core/Log.hpp"
#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Lithe
{
    /// Static class for keyboard info
    class Keyboard
    {
    public:
        /// Enum for all keyboard keys
        enum class Key
        {
            Unknown = 1,

            Space,
            Apostrophe,         /*!< ' */
            Comma,              /*!< , */
            Minus,              /*!< \- */
            Period,             /*!< \. */
            Slash,              /*!< / */
            Key0,
            Key1,
            Key2,
            Key3,
            Key4,
            Key5,
            Key6,
            Key7,
            Key8,
            Key9,
            Semicolon,          /*!< ; */
            EQUAL,              /*!< = */
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            LeftBracket,       /*!< [ */
            Backslash,         /*!< \ */
            RightBracket,      /*!< ] */
            GraveAccent,       /*!< ` */
            World1,            /*!< non-US #1 */
            World2,            /*!< non-US #2 */


            // --- Func keys ---
            Escape,
            Enter,
            Tab,
            Backspace,
            Insert,
            Delete,
            Right,
            Left,
            Down,
            Up,
            PageUp,
            PageDown,
            Home,
            End,
            CapsLock,
            ScrollLock,
            NumLock,
            PrintScreen,
            Pause,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24,
            F25,
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            NumDecimal,
            NumDivide,
            NumMultiply,
            NumSubstract,
            NumAdd,
            NumEnter,
            NumEqual,
            LeftShift,
            LeftControl,
            LeftAlt,
            LeftSuper,
            RightShift,
            RightControl,
            RightAlt,
            RightSuper,
            Menu,

            Count
        };

        /**
         * @brief Converts Lithe Keyboard::Key enum element to Glfw int code
         * @param key Key to convert
         * @return Glfw key code
        */
        static int ToGlfwKey(const Key& key)
        {
            switch (key)
            {
            case Key::Unknown:              return GLFW_KEY_UNKNOWN;
            case Key::Space:                return GLFW_KEY_SPACE;
            case Key::Apostrophe:           return GLFW_KEY_APOSTROPHE;
            case Key::Comma:                return GLFW_KEY_COMMA;
            case Key::Minus:                return GLFW_KEY_MINUS;
            case Key::Period:               return GLFW_KEY_PERIOD;
            case Key::Slash:                return GLFW_KEY_SLASH;
            case Key::Key0:                 return GLFW_KEY_0;
            case Key::Key1:                 return GLFW_KEY_1;
            case Key::Key2:                 return GLFW_KEY_2;
            case Key::Key3:                 return GLFW_KEY_3;
            case Key::Key4:                 return GLFW_KEY_4;
            case Key::Key5:                 return GLFW_KEY_5;
            case Key::Key6:                 return GLFW_KEY_6;
            case Key::Key7:                 return GLFW_KEY_7;
            case Key::Key8:                 return GLFW_KEY_8;
            case Key::Key9:                 return GLFW_KEY_9;
            case Key::Semicolon:            return GLFW_KEY_SEMICOLON;
            case Key::EQUAL:                return GLFW_KEY_EQUAL;
            case Key::A:                    return GLFW_KEY_A;
            case Key::B:                    return GLFW_KEY_B;
            case Key::C:                    return GLFW_KEY_C;
            case Key::E:                    return GLFW_KEY_E;
            case Key::F:                    return GLFW_KEY_F;
            case Key::G:                    return GLFW_KEY_G;
            case Key::H:                    return GLFW_KEY_H;
            case Key::I:                    return GLFW_KEY_I;
            case Key::J:                    return GLFW_KEY_J;
            case Key::K:                    return GLFW_KEY_K;
            case Key::L:                    return GLFW_KEY_L;
            case Key::M:                    return GLFW_KEY_M;
            case Key::N:                    return GLFW_KEY_N;
            case Key::O:                    return GLFW_KEY_O;
            case Key::P:                    return GLFW_KEY_P;
            case Key::Q:                    return GLFW_KEY_Q;
            case Key::R:                    return GLFW_KEY_R;
            case Key::S:                    return GLFW_KEY_S;
            case Key::T:                    return GLFW_KEY_T;
            case Key::U:                    return GLFW_KEY_U;
            case Key::V:                    return GLFW_KEY_V;
            case Key::W:                    return GLFW_KEY_W;
            case Key::X:                    return GLFW_KEY_X;
            case Key::Y:                    return GLFW_KEY_Y;
            case Key::Z:                    return GLFW_KEY_Z;
            case Key::LeftBracket:          return GLFW_KEY_LEFT_BRACKET;
            case Key::Backslash:            return GLFW_KEY_BACKSLASH;
            case Key::RightBracket:         return GLFW_KEY_RIGHT_BRACKET;
            case Key::GraveAccent:          return GLFW_KEY_GRAVE_ACCENT;
            case Key::World1:               return GLFW_KEY_WORLD_1;
            case Key::World2:               return GLFW_KEY_WORLD_2;


            case Key::Escape:               return GLFW_KEY_ESCAPE;
            case Key::Enter:                return GLFW_KEY_ENTER;
            case Key::Tab:                  return GLFW_KEY_TAB;
            case Key::Backspace:            return GLFW_KEY_BACKSPACE;
            case Key::Insert:               return GLFW_KEY_INSERT;
            case Key::Delete:               return GLFW_KEY_DELETE;
            case Key::Right:                return GLFW_KEY_RIGHT;
            case Key::Left:                 return GLFW_KEY_LEFT;
            case Key::Down:                 return GLFW_KEY_DOWN;
            case Key::Up:                   return GLFW_KEY_UP;
            case Key::PageUp:               return GLFW_KEY_PAGE_UP;
            case Key::PageDown:             return GLFW_KEY_PAGE_DOWN;
            case Key::Home:                 return GLFW_KEY_HOME;
            case Key::End:                  return GLFW_KEY_END;
            case Key::CapsLock:             return GLFW_KEY_CAPS_LOCK;
            case Key::ScrollLock:           return GLFW_KEY_SCROLL_LOCK;
            case Key::NumLock:              return GLFW_KEY_NUM_LOCK;
            case Key::PrintScreen:          return GLFW_KEY_PRINT_SCREEN;
            case Key::Pause:                return GLFW_KEY_PAUSE;
            case Key::F1:                   return GLFW_KEY_F1;
            case Key::F2:                   return GLFW_KEY_F2;
            case Key::F3:                   return GLFW_KEY_F3;
            case Key::F4:                   return GLFW_KEY_F4;
            case Key::F5:                   return GLFW_KEY_F5;
            case Key::F6:                   return GLFW_KEY_F6;
            case Key::F7:                   return GLFW_KEY_F7;
            case Key::F8:                   return GLFW_KEY_F8;
            case Key::F9:                   return GLFW_KEY_F9;
            case Key::F10:                  return GLFW_KEY_F10;
            case Key::F11:                  return GLFW_KEY_F11;
            case Key::F12:                  return GLFW_KEY_F12;
            case Key::F13:                  return GLFW_KEY_F13;
            case Key::F14:                  return GLFW_KEY_F14;
            case Key::F15:                  return GLFW_KEY_F15;
            case Key::F16:                  return GLFW_KEY_F16;
            case Key::F17:                  return GLFW_KEY_F17;
            case Key::F18:                  return GLFW_KEY_F18;
            case Key::F19:                  return GLFW_KEY_F19;
            case Key::F20:                  return GLFW_KEY_F20;
            case Key::F21:                  return GLFW_KEY_F21;
            case Key::F22:                  return GLFW_KEY_F22;
            case Key::F23:                  return GLFW_KEY_F23;
            case Key::F24:                  return GLFW_KEY_F24;
            case Key::F25:                  return GLFW_KEY_F25;
            case Key::Num0:                 return GLFW_KEY_KP_0;
            case Key::Num1:                 return GLFW_KEY_KP_1;
            case Key::Num2:                 return GLFW_KEY_KP_2;
            case Key::Num3:                 return GLFW_KEY_KP_3;
            case Key::Num4:                 return GLFW_KEY_KP_4;
            case Key::Num5:                 return GLFW_KEY_KP_5;
            case Key::Num6:                 return GLFW_KEY_KP_6;
            case Key::Num7:                 return GLFW_KEY_KP_7;
            case Key::Num8:                 return GLFW_KEY_KP_8;
            case Key::Num9:                 return GLFW_KEY_KP_9;
            case Key::NumDecimal:           return GLFW_KEY_KP_DECIMAL;
            case Key::NumDivide:            return GLFW_KEY_KP_DIVIDE;
            case Key::NumMultiply:          return GLFW_KEY_KP_MULTIPLY;
            case Key::NumSubstract:         return GLFW_KEY_KP_SUBTRACT;
            case Key::NumAdd:               return GLFW_KEY_KP_ADD;
            case Key::NumEnter:             return GLFW_KEY_KP_ENTER;
            case Key::NumEqual:             return GLFW_KEY_KP_EQUAL;
            case Key::LeftShift:            return GLFW_KEY_LEFT_SHIFT;
            case Key::LeftControl:          return GLFW_KEY_LEFT_CONTROL;
            case Key::LeftAlt:              return GLFW_KEY_LEFT_ALT;
            case Key::LeftSuper:            return GLFW_KEY_LEFT_SUPER;
            case Key::RightShift:           return GLFW_KEY_RIGHT_SHIFT;
            case Key::RightControl:         return GLFW_KEY_RIGHT_CONTROL;
            case Key::RightAlt:             return GLFW_KEY_RIGHT_ALT;
            case Key::RightSuper:           return GLFW_KEY_RIGHT_SUPER;
            case Key::Menu:                 return GLFW_KEY_MENU;



            default:
                LITHE_CORE_WARN("Key unknown to Glfw!");
                break;
            }
        }

    private:
        static const std::unordered_map<Key, int> s_GlfwKeyMap;
    };

    const std::unordered_map<Keyboard::Key, int> Keyboard::s_GlfwKeyMap =
    {
        {Key::Unknown          , GLFW_KEY_UNKNOWN },
        {Key::Space            , GLFW_KEY_SPACE },
        {Key::Apostrophe       , GLFW_KEY_APOSTROPHE },
        {Key::Comma            , GLFW_KEY_COMMA },
        {Key::Minus            , GLFW_KEY_MINUS },
        {Key::Period           , GLFW_KEY_PERIOD },
        {Key::Slash            , GLFW_KEY_SLASH },
        {Key::Key0             , GLFW_KEY_0 },
        {Key::Key1             , GLFW_KEY_1 },
        {Key::Key2             , GLFW_KEY_2 },
        {Key::Key3             , GLFW_KEY_3 },
        {Key::Key4             , GLFW_KEY_4 },
        {Key::Key5             , GLFW_KEY_5 },
        {Key::Key6             , GLFW_KEY_6 },
        {Key::Key7             , GLFW_KEY_7 },
        {Key::Key8             , GLFW_KEY_8 },
        {Key::Key9             , GLFW_KEY_9 },
        {Key::Semicolon        , GLFW_KEY_SEMICOLON },
        {Key::EQUAL            , GLFW_KEY_EQUAL },
        {Key::A                , GLFW_KEY_A },
        {Key::B                , GLFW_KEY_B },
        {Key::C                , GLFW_KEY_C },
        {Key::E                , GLFW_KEY_E },
        {Key::F                , GLFW_KEY_F },
        {Key::G                , GLFW_KEY_G },
        {Key::H                , GLFW_KEY_H },
        {Key::I                , GLFW_KEY_I },
        {Key::J                , GLFW_KEY_J },
        {Key::K                , GLFW_KEY_K },
        {Key::L                , GLFW_KEY_L },
        {Key::M                , GLFW_KEY_M },
        {Key::N                , GLFW_KEY_N },
        {Key::O                , GLFW_KEY_O },
        {Key::P                , GLFW_KEY_P },
        {Key::Q                , GLFW_KEY_Q },
        {Key::R                , GLFW_KEY_R },
        {Key::S                , GLFW_KEY_S },
        {Key::T                , GLFW_KEY_T },
        {Key::U                , GLFW_KEY_U },
        {Key::V                , GLFW_KEY_V },
        {Key::W                , GLFW_KEY_W },
        {Key::X                , GLFW_KEY_X },
        {Key::Y                , GLFW_KEY_Y },
        {Key::Z                , GLFW_KEY_Z },
        {Key::LeftBracket      , GLFW_KEY_LEFT_BRACKET },
        {Key::Backslash        , GLFW_KEY_BACKSLASH },
        {Key::RightBracket     , GLFW_KEY_RIGHT_BRACKET },
        {Key::GraveAccent      , GLFW_KEY_GRAVE_ACCENT },
        {Key::World1           , GLFW_KEY_WORLD_1 },
        {Key::World2           , GLFW_KEY_WORLD_2 },
        {Key::Escape           , GLFW_KEY_ESCAPE },
        {Key::Enter            , GLFW_KEY_ENTER },
        {Key::Tab              , GLFW_KEY_TAB },
        {Key::Backspace        , GLFW_KEY_BACKSPACE },
        {Key::Insert           , GLFW_KEY_INSERT },
        {Key::Delete           , GLFW_KEY_DELETE },
        {Key::Right            , GLFW_KEY_RIGHT },
        {Key::Left             , GLFW_KEY_LEFT },
        {Key::Down             , GLFW_KEY_DOWN },
        {Key::Up               , GLFW_KEY_UP },
        {Key::PageUp           , GLFW_KEY_PAGE_UP },
        {Key::PageDown         , GLFW_KEY_PAGE_DOWN },
        {Key::Home             , GLFW_KEY_HOME },
        {Key::End              , GLFW_KEY_END },
        {Key::CapsLock         , GLFW_KEY_CAPS_LOCK },
        {Key::ScrollLock       , GLFW_KEY_SCROLL_LOCK },
        {Key::NumLock          , GLFW_KEY_NUM_LOCK },
        {Key::PrintScreen      , GLFW_KEY_PRINT_SCREEN },
        {Key::Pause            , GLFW_KEY_PAUSE },
        {Key::F1               , GLFW_KEY_F1 },
        {Key::F2               , GLFW_KEY_F2 },
        {Key::F3               , GLFW_KEY_F3 },
        {Key::F4               , GLFW_KEY_F4 },
        {Key::F5               , GLFW_KEY_F5 },
        {Key::F6               , GLFW_KEY_F6 },
        {Key::F7               , GLFW_KEY_F7 },
        {Key::F8               , GLFW_KEY_F8 },
        {Key::F9               , GLFW_KEY_F9 },
        {Key::F10              , GLFW_KEY_F10 },
        {Key::F11              , GLFW_KEY_F11 },
        {Key::F12              , GLFW_KEY_F12 },
        {Key::F13              , GLFW_KEY_F13 },
        {Key::F14              , GLFW_KEY_F14 },
        {Key::F15              , GLFW_KEY_F15 },
        {Key::F16              , GLFW_KEY_F16 },
        {Key::F17              , GLFW_KEY_F17 },
        {Key::F18              , GLFW_KEY_F18 },
        {Key::F19              , GLFW_KEY_F19 },
        {Key::F20              , GLFW_KEY_F20 },
        {Key::F21              , GLFW_KEY_F21 },
        {Key::F22              , GLFW_KEY_F22 },
        {Key::F23              , GLFW_KEY_F23 },
        {Key::F24              , GLFW_KEY_F24 },
        {Key::F25              , GLFW_KEY_F25 },
        {Key::Num0             , GLFW_KEY_KP_0 },
        {Key::Num1             , GLFW_KEY_KP_1 },
        {Key::Num2             , GLFW_KEY_KP_2 },
        {Key::Num3             , GLFW_KEY_KP_3 },
        {Key::Num4             , GLFW_KEY_KP_4 },
        {Key::Num5             , GLFW_KEY_KP_5 },
        {Key::Num6             , GLFW_KEY_KP_6 },
        {Key::Num7             , GLFW_KEY_KP_7 },
        {Key::Num8             , GLFW_KEY_KP_8 },
        {Key::Num9             , GLFW_KEY_KP_9 },
        {Key::NumDecimal       , GLFW_KEY_KP_DECIMAL },
        {Key::NumDivide        , GLFW_KEY_KP_DIVIDE },
        {Key::NumMultiply      , GLFW_KEY_KP_MULTIPLY },
        {Key::NumSubstract     , GLFW_KEY_KP_SUBTRACT },
        {Key::NumAdd           , GLFW_KEY_KP_ADD },
        {Key::NumEnter         , GLFW_KEY_KP_ENTER },
        {Key::NumEqual         , GLFW_KEY_KP_EQUAL },
        {Key::LeftShift        , GLFW_KEY_LEFT_SHIFT },
        {Key::LeftControl      , GLFW_KEY_LEFT_CONTROL },
        {Key::LeftAlt          , GLFW_KEY_LEFT_ALT },
        {Key::LeftSuper        , GLFW_KEY_LEFT_SUPER },
        {Key::RightShift       , GLFW_KEY_RIGHT_SHIFT },
        {Key::RightControl     , GLFW_KEY_RIGHT_CONTROL },
        {Key::RightAlt         , GLFW_KEY_RIGHT_ALT },
        {Key::RightSuper       , GLFW_KEY_RIGHT_SUPER },
        {Key::Menu             , GLFW_KEY_MENU }
    };
}