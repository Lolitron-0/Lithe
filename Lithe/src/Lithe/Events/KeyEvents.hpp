/*****************************************************************//**
 * @file   KeyEvents.hpp
 * @brief  Header file describing all keyboard related events (key pressed/released).
 *
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Input/Keyboard.hpp"
#include "Event.hpp"

namespace Lithe
{
    /**
     * @brief Base class for all keyboard events
     *
     * All KeyEvents have information about code of the key and have EventCategory: EventCategoryInput, EventCategoryKeyboard.
     */
    class LITHE_API KeyEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard);

        /**
         * Getter of the key code of this event.
         * @return Key code as Lithe enum element
         */
        Keyboard::Key GetKeyCode() const { return m_KeyCode; }
    protected:
        KeyEvent(Keyboard::Key keyCode)
            :m_KeyCode(keyCode)
        {}
    private:
        Keyboard::Key m_KeyCode;
    };

    /**
     * @brief Class for key press event.
     *
     * Has EventType::KeyPressedType
     */
    class LITHE_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(Keyboard::Key keyCode, bool isRepeated)
            :KeyEvent(keyCode), m_IsRepeated(isRepeated)
        {}

        /**
         * Each key press event has a repeat flag. Delay between key press and key repeat may vary on different systems.
         *
         * @return Repeat flag of this event.
         */
        bool IsRepeated() const { return m_IsRepeated; }

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressed: key=" << Keyboard::KeyToString(GetKeyCode()) << " repeat=" << (m_IsRepeated ? "true" : "false");
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeated;
    };

    /**
     * @brief Class for key release event.
     *
     * Has EventType::KeyRelease type
     */
    class LITHE_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(Keyboard::Key keyCode)
            :KeyEvent(keyCode)
        {}

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleased: key=" << Keyboard::KeyToString(GetKeyCode());
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

}
