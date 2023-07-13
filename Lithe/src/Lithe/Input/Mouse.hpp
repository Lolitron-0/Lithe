#pragma once
#include "Lithe/Core/Math.hpp"

namespace Lithe
{

    /// Static class describing mouse states.
    class LITHE_API Mouse
    {
    public:
        /**
         * @brief Lithe mouse button codes
        */
        enum class Button
        {
            Button1,
            Button2,
            Button3,
            Button4,
            Button5,
            Button6,
            Button7,
            Button8,

            Left,	/*!< LMB */
            Right,	/*!< RMB */
            Middle	/*!< CMB */
        };

        static bool IsButtonPressed(const Mouse::Button& button) { return s_Instance->IsButtonPressedImpl(button); }

        static Vec2 GetPosition() { return s_Instance->GetPositionImpl(); };

        /**
         * @brief Converts Mouse::Butoon enum element to string
         * @param button Button to convert
         * @return String representation
        */
        static std::string ButtonToString(Button button);

    protected:
        virtual bool IsButtonPressedImpl(const Mouse::Button& button) = 0;

        virtual Vec2 GetPositionImpl() = 0;

    private:
        static const std::unordered_map<Button, std::string> s_ButtonToStringMap;

        static Mouse* s_Instance; // For polymorphism
    };


}
