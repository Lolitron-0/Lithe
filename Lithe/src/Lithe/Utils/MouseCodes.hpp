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

        /**
         * @brief Converts Lithe key codes enum to Glfw notation
         * @param button Key code to convert
         * @return Glfw defined code
        */
        static int ToGlfwMouseButton(const Button& button);

        /**
         * @brief Converts Glfw mouse button code to Mouse::Button enum element
         * @param glfwButton Code to convert
         * @return Mouse::Button enum element
        */
        static Button FromGlfwMouseButton(int glfwButton);

        static const std::unordered_map<Button, int> s_ButtonToGlfwMap;
        static std::unordered_map<int, Button> s_GlfwToButtonMap;

    };


}
