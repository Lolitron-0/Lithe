#pragma once
#include "Lithe/Input/Keyboard.hpp"
#include <unordered_map>

namespace Lithe
{
    class WindowsKeyboard final : public Keyboard
    {
    public:
        bool IsKeyPressedImpl(const Key& key) const override;

    private:
        static const std::unordered_map<Key, int> s_KeyToGlfwMap;
        static std::unordered_map<int, Key> s_GlfwToKeyMap;

        friend int ToGlfwKey(const Keyboard::Key& key);
        friend Keyboard::Key FromGlfwKey(int glfwKey);
    };

    /**
     * @brief Converts Lithe Keyboard::Key enum element to Glfw int code
     * @param key Key to convert
     * @return Glfw key code
    */
    int ToGlfwKey(const Keyboard::Key& key);

    /**
     * @brief Converts Glfw key code to Lithe enum element
     * @param glfwKey Code to convert
     * @return Keyboard::Key enum element
    */
    Keyboard::Key FromGlfwKey(int glfwKey);
}
