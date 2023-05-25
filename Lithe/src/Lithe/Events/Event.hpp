/*****************************************************************//**
 * \file   Event.hpp
 * \brief  
 * 
 * \author Lolitron
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "Lithe/Core.hpp"
#include "spdlog/fmt/ostr.h"

namespace Lithe
{
	enum class EventType
	{
		None=0,
		WindowResized, WindowClosed, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScroll,
		AppUpdate, AppRender, AppTick,
		
		Count
	};

	enum EventCategory
	{
		None=0,
		Application			=BIT(0),
		Input				=BIT(1),
		Keyboard			=BIT(2),
		Mouse				=BIT(3),
		MouseButton			=BIT(4),
		Window				=BIT(5),
	};

// ------------- MACROS -------------

// static type getter is for templates
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags() const override {return category;}

// ----------------------------------

	class LITHE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	private:
		bool handled_{ false };
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
