#pragma once
#include "Lithe/Core/Base.hpp"

namespace Lithe
{
	
	///brief Static class describing mouse states.
	class LITHE_API Mouse
	{
	public:
		enum class Button
		{
			Left,	/*!< LMB */
			Right,	/*!< RMB */
			Middle	/*!< CMB */
		};
	};

}
