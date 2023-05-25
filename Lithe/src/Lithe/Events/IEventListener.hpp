#pragma once
#include "Event.hpp"

namespace Lithe {

	class IEventListener
	{
	public:
		virtual void OnEvent(const Event&)=0;
	};

}