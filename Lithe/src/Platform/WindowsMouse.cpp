#include "WindowsMouse.hpp"
#include "Lithe/Core/Log.hpp"
#include "Lithe/Core/Application.hpp"
#include <GLFW/glfw3.h>

namespace Lithe
{
    const std::unordered_map<Mouse::Button, int> WindowsMouse::s_ButtonToGlfwMap
    {
        { Mouse::Button::Left,          GLFW_MOUSE_BUTTON_LEFT},
        { Mouse::Button::Right,         GLFW_MOUSE_BUTTON_RIGHT },
        { Mouse::Button::Middle,	    GLFW_MOUSE_BUTTON_MIDDLE },
        { Mouse::Button::Button1,	    GLFW_MOUSE_BUTTON_1 },
        { Mouse::Button::Button2,	    GLFW_MOUSE_BUTTON_2 },
        { Mouse::Button::Button3,	    GLFW_MOUSE_BUTTON_3 },
        { Mouse::Button::Button4,	    GLFW_MOUSE_BUTTON_4 },
        { Mouse::Button::Button5,	    GLFW_MOUSE_BUTTON_5 },
        { Mouse::Button::Button6,	    GLFW_MOUSE_BUTTON_6 },
        { Mouse::Button::Button7,	    GLFW_MOUSE_BUTTON_7 },
        { Mouse::Button::Button8,	    GLFW_MOUSE_BUTTON_8 }
    };

    std::unordered_map<int, Mouse::Button> WindowsMouse::s_GlfwToButtonMap{};


    int ToGlfwMouseButton(const Mouse::Button& button)
    {
        try
        {
            return WindowsMouse::s_ButtonToGlfwMap.at(button);
        }
        catch (const std::exception& e)
        {
            LITHE_CORE_WARN("Caught unknown mouse button!")
        }
        return -1;
    }
    Mouse::Button FromGlfwMouseButton(int glfwButton)
    {
        if (WindowsMouse::s_GlfwToButtonMap.size() == 0)
            for (auto&& it : WindowsMouse::s_ButtonToGlfwMap)
                WindowsMouse::s_GlfwToButtonMap[it.second] = it.first;

        return WindowsMouse::s_GlfwToButtonMap.at(glfwButton);
    }
    bool WindowsMouse::IsButtonPressedImpl(const Mouse::Button& button)
    {
        auto& window = Application::GetInstance().GetWindow();
        auto status = glfwGetMouseButton(window.GetNativeHandle<GLFWwindow*>(), ToGlfwMouseButton(button));
        return status == GLFW_PRESS;
    }
}
