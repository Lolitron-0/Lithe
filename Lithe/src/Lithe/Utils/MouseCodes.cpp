#include "MouseCodes.hpp"
#include "Lithe/Core/Log.hpp"
#include <GLFW/glfw3.h>


namespace Lithe
{
    const std::unordered_map<Mouse::Button, int> Mouse::s_ButtonToGlfwMap =
    {
        { Button::Left,         GLFW_MOUSE_BUTTON_LEFT},
        { Button::Right,        GLFW_MOUSE_BUTTON_RIGHT },
        { Button::Middle,	    GLFW_MOUSE_BUTTON_MIDDLE },
        { Button::Button1,	    GLFW_MOUSE_BUTTON_1 },
        { Button::Button2,	    GLFW_MOUSE_BUTTON_2 },
        { Button::Button3,	    GLFW_MOUSE_BUTTON_3 },
        { Button::Button4,	    GLFW_MOUSE_BUTTON_4 },
        { Button::Button5,	    GLFW_MOUSE_BUTTON_5 },
        { Button::Button6,	    GLFW_MOUSE_BUTTON_6 },
        { Button::Button7,	    GLFW_MOUSE_BUTTON_7 },
        { Button::Button8,	    GLFW_MOUSE_BUTTON_8 }
    };

    std::unordered_map<int, Mouse::Button> Mouse::s_GlfwToButtonMap{};

    int Mouse::ToGlfwMouseButton(const Button& button)
    {
        try
        {
            return s_ButtonToGlfwMap.at(button);
        }
        catch (const std::exception& e)
        {
            LITHE_CORE_WARN("Caught unknown mouse button!")
        }
        return -1;
    }

    Mouse::Button Mouse::FromGlfwMouseButton(int glfwButton)
    {
        if (Mouse::s_GlfwToButtonMap.size() == 0)
            for (auto&& it : Mouse::s_ButtonToGlfwMap)
                Mouse::s_GlfwToButtonMap[it.second] = it.first;

        return s_GlfwToButtonMap.at(glfwButton);
    }
}