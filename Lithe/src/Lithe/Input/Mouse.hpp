#pragma once
#include "Lithe/Core/Base.hpp"
#include <unordered_map>


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


    protected:
        virtual bool IsButtonPressedImpl(const Mouse::Button& button) = 0;

        static Mouse* s_Instance; // For polymorphism

    };


}
