/*****************************************************************//**
 * @file   MouseEvents.hpp
 * @brief  Header file describing all mouse related events.
 *
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Input/Mouse.hpp"
#include "Event.hpp"

namespace Lithe
{
    /**
     * @brief Class for mouse move event.
     *
     * Belongs to EventCategoryMouse and EventCategoryInput category
     * and EventType::MouseMoved type
     */
    class LITHE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float mouseX, float mouseY)
            : m_MouseX(mouseX), m_MouseY(mouseY)
        {}

        /**
         * @brief Mouse y position getter.
         * \todo position coordinate system
         *
         * @return cursor y position in some coordinate system :^)
         */
        float GetMouseX() const { return m_MouseX; }
        /**
        * @brief Mouse x position getter.
        * \todo position coordinate system
        *
        * @return cursor x position in some coordinate system :^)
        */
        float GetMouseY() const { return m_MouseY; }

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
    };

    /**
     * @brief Base class for all mouse button events.
     *
     * Belongs to EventCategoryMouse and EventCategoryInput category
     */
    class LITHE_API MouseButtonEvent : public Event
    {
    public:
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
            /**
             * @brief Mouse button getter.
             *
             * @return Element of Mouse::Button enum
             */
            Mouse::Button GetMouseButton() const { return m_Button; }

    protected:
        MouseButtonEvent(Mouse::Button button)
            :m_Button(button)
        {}
    private:
        Mouse::Button m_Button;
    };

    /**
    * @brief Class for mouse press button event.
    *
    * Has EventType::MouseButtonPressed type
    */
    class LITHE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(Mouse::Button button)
            :MouseButtonEvent(button)
        {}

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressed: button=" << Mouse::ButtonToString(GetMouseButton());
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    /**
    * @brief Class for mouse release button event.
    *
    * Has EventType::MouseButtonReleased type
    */
    class LITHE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(Mouse::Button button)
            :MouseButtonEvent(button)
        {}
        
        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleased: button=" << Mouse::ButtonToString(GetMouseButton());
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    /**
     * @brief Class for mouse scroll event
     *
     * Has EventType::MouseScrolled and Input | Mouse categories
    */
    class LITHE_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float offsetX, float offsetY)
            : m_OffsetX(offsetX), m_OffsetY(offsetY)
        {}

        /**
         * @brief Scroll x offset getter.
         *
         * @return x scroll offset
         */
        float GetOffsetX() const { return m_OffsetX; }
        /**
        * @brief Scroll y offset getter.
        *
        * @return y scroll offset
        */
        float GetOffsetY() const { return m_OffsetY; }

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_OffsetX, m_OffsetY;
    };
}