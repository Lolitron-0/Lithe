/*****************************************************************//**
 * @file   KeyEvents.hpp
 * @brief  Header file describing all keyboard related events (key pressed/released).
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
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
		 * \todo key code notation
		 * @return Key code in some notation :^)
		 */
		int GetKeyCode() const { return m_KeyCode; }
	protected:
		KeyEvent(int keyCode)
			:m_KeyCode(keyCode)
		{}
	private:
		int m_KeyCode;
	};

	/**
	 * @brief Class for key press event.
	 * 
	 * Has EventType::KeyPressedType
	 */
	class LITHE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), m_RepeatCount(repeatCount)
		{}

		/**
		 * Each key press event has a repeat counter. Delay between key press and key repeat may vary on different systems..
		 * 
		 * @return Repeat count of this event.
		 */
		int GetRepeatCount() const { return m_RepeatCount; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << GetKeyCode() << " repeat=" << m_RepeatCount;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	/**
	 * @brief Class for key release event.
	 * 
	 * Has EventType::KeyRelease type
	 */
	class LITHE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode)
		{}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleased: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
