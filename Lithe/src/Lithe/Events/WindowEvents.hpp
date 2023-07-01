/*****************************************************************//**
 * @file   WindowEvents.hpp
 * @brief  File describing classes for all window related events
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include "Event.hpp"


namespace Lithe
{
	/// Class for WindowClosed event type, without any specific data
	class LITHE_API WindowClosedEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryWindow);
		EVENT_CLASS_TYPE(WindowClosed);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}
	};

	/// Class for WindowResized event type, contains new size of window
	class LITHE_API WindowResizedEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryWindow);
		EVENT_CLASS_TYPE(WindowResized);

		WindowResizedEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height)
		{}

		/// Getter for new window x size
		int GetNewWidth() const { return m_Width; }
		/// Getter for new window y size
		int GetNewHeight() const { return m_Height; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};

	/// Class for WindowGainedFocus event type, without any specific data
	class LITHE_API WindowGainedFocusEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryWindow);
		EVENT_CLASS_TYPE(WindowGainedFocus);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}
	};

	/// Class for WindowLostFocus event type, without any specific data
	class LITHE_API WindowLostFocusEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryWindow);
		EVENT_CLASS_TYPE(WindowLostFocus);

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}
	};

	/**
	 * @brief Class for WindowMoved event type, holds offset values.
	 * \todo look up actual implementation (in GLFW)
	 */
	class LITHE_API WindowMovedEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryWindow);
		EVENT_CLASS_TYPE(WindowLostFocus);

		WindowMovedEvent(int offsetX, int offsetY)
			:m_OffsetX(offsetX), m_OffsetY(offsetY)
		{}

		/// Getter for move offset x value
		int GetOffsetX() const { return m_OffsetX; }
		/// Getter for move offset y value
		int GetOffsetY() const { return m_OffsetY; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowClosedEvent";
			return ss.str();
		}
	private:
		int m_OffsetX;
		int m_OffsetY;
	};

}
