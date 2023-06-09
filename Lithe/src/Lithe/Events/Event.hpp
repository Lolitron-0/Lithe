/*****************************************************************//**
 * @file   Event.hpp
 * @brief  Event system core stuff
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core/Base.hpp"
#include <sstream>
#include "Lithe/Core/Log.hpp"

namespace Lithe
{

	/// Enum class for all (?) event types
	enum class EventType
	{
		None=0,
		WindowResized, WindowClosed, WindowGainedFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		AppUpdate, AppRender, AppTick,
		
		Count
	};

	/**
	 * @brief C-style enum for sorting Events by btfield category
	 * 
	 * Not enum class so Event inheritants can use bit OR ('|') in class category definition macro easily 
	 * (without specifying enum class for each category flag)
	 */
	enum EventCategory
	{
		None=0,
		EventCategoryApplication			=BIT(0),
		EventCategoryInput					=BIT(1),
		EventCategoryKeyboard				=BIT(2),
		EventCategoryMouse					=BIT(3),
		EventCategoryMouseButton			=BIT(4),
		EventCategoryWindow					=BIT(5),
	};

// ------------- MACROS -------------

// static type getter is for templates
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags() const override {return category;}

// ----------------------------------

	/**
	 * @brief Base class for all event types, categories and sources.
	 */
	class LITHE_API Event
	{
		friend class EventDispatcher;
	public:
		/// Returns enum class type element for this Event
		virtual EventType GetEventType() const = 0;
		/// Returns category flags bitfield
		virtual int GetCategoryFlags() const = 0;
		/// Returns class name (for debugging purposes)
		virtual const char* GetName() const = 0;
		/// C#-style method for logging and debugging purposes
		virtual std::string ToString() const = 0;

		/// Checks if this event belongs to specified category/categories
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}


		bool Handled{ false };
	};

	// Operator for spdlog output
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}


	/**
	 * @brief An event dispatcher class.
	 * 
	 * Wraps an event and can be used to invoke callback functions of different types for it.
	 * i.e. for some event we simply wrap it in dispatcher and call dispatcher->Dispatch<MouseMoveEvent>(someMouseMoveCallbackRef),
	 * if type check fails, dispatcher won't invoke that callback
	 */
	class LITHE_API EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			:m_Event(e)
		{}

		/**
		 * @brief Tries to notify about this event using provided callback.
		 * 
		 * Checks if type of template matches. If so, invokes callback and sets proper status to the event
		 * 
		 * @param func - Callback that will be invoked if type matches. Return value should be bool - indicating if event was handled or should be propagated further
		 * @return Result of a type check
		 */
		template <class T, class F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}
