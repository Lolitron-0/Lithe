#pragma once

namespace Lithe
{
    /// Static class for keyboard info
    class LITHE_API Keyboard
    {
    public:
        /// Enum for all keyboard keys
        enum class Key
        {
            Unknown = -1,

            Space = 1,
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

        static bool IsKeyPressed(const Key& key) { return s_Instance->IsKeyPressedImpl(key); }
    
        /**
         * @brief Converts Lithe Keyboard::Key to string
         * @param key Key to convert
         * @return String representation
        */
        static std::string KeyToString(Key key);
        
protected:
        virtual bool IsKeyPressedImpl(const Key& key) const = 0;
    private:
        static const std::unordered_map<Key, std::string> s_KeyToStringMap;

        static Keyboard* s_Instance; // not actually a singleton, used for polymorphism
    };

}