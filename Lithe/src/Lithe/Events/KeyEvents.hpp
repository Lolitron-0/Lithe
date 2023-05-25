/*****************************************************************//**
 * \file   KeyEvents.hpp
 * \brief  Header file describing all keyboard related events (key pressed/released).
 * 
 * \author Lolitron
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe//Core/Base.hpp"
#include "Event.hpp"

namespace Lithe
{
	/**
	 * \brief Base class for all keyboard events
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
		 * \return Key code in some notation :^)
		 */
		inline int GetKeyCode() const { return keyCode_; }
	protected:
		KeyEvent(int keyCode)
			:keyCode_(keyCode)
		{}
	private:
		int keyCode_;
	};

	/**
	 * \brief Class for key press event.
	 * 
	 * Has EventType::KeyPressedType
	 */
	class LITHE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode), repeatCount_(repeatCount)
		{}

		/**
		 * Each key press event has a repeat counter. Delay between key press and key repeat may vary on different systems..
		 * 
		 * \return Repeat count of this event.
		 */
		inline int GetRepeatCount() const { return repeatCount_; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed: " << GetKeyCode() << " repeat=" << repeatCount_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount_;
	};

	/**
	 * \brief Class for key release event.
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
