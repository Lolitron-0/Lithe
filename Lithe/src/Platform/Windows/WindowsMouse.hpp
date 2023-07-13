#pragma once
#include "Lithe/Input/Mouse.hpp"

namespace Lithe
{
    /// Mouse class implementation for Windows
    class WindowsMouse final : public Mouse
    {
    public:
        bool IsButtonPressedImpl(const Mouse::Button& button) override;

        Vec2 GetPositionImpl() override;
    private:

        static const std::unordered_map<Button, int> s_ButtonToGlfwMap;
        static std::unordered_map<int, Button> s_GlfwToButtonMap;

        friend int ToGlfwMouseButton(const Mouse::Button& button);
        friend Mouse::Button FromGlfwMouseButton(int glfwButton);
    };

    /**
     * @brief Converts Lithe key codes enum to Glfw notation
     * @param button Key code to convert
     * @return Glfw defined code
    */
    int ToGlfwMouseButton(const Mouse::Button& button);

    /**
     * @brief Converts Glfw mouse button code to Mouse::Button enum element
     * @param glfwButton Code to convert
     * @return Mouse::Button enum element
    */
    Mouse::Button FromGlfwMouseButton(int glfwButton);
}
