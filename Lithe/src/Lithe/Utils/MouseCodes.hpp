#pragma once
#include "Lithe/Core/Base.hpp"
#include "Lithe/Core/Log.hpp"
#include <GLFW/glfw3.h>

namespace Lithe
{
	
	/// Static class describing mouse states.
	class LITHE_API Mouse
	{
	public:
		/**
		 * @brief Lithe mouse button codes
		*/
		enum class Button
		{
			Button1,
			Button2,
			Button3,
			Button4,
			Button5,
			Button6,
			Button7,
			Button8,

			Left,	/*!< LMB */
			Right,	/*!< RMB */
			Middle	/*!< CMB */
		};

		/**
		 * @brief Converts Lithe key codes enum to Glfw notation
		 * @param button Key code to convert
		 * @return Glfw defined 
		*/
		static int ToGlfwMouseButtonCode(const Button& button)
		{
			switch (button)
			{
			case Button::Left: return GLFW_MOUSE_BUTTON_LEFT;
			case Button::Right: return GLFW_MOUSE_BUTTON_RIGHT;
			case Button::Middle: return GLFW_MOUSE_BUTTON_MIDDLE;
			case Button::Button1: return GLFW_MOUSE_BUTTON_1;
			case Button::Button2: return GLFW_MOUSE_BUTTON_2;
			case Button::Button3: return GLFW_MOUSE_BUTTON_3;
			case Button::Button4: return GLFW_MOUSE_BUTTON_4;
			case Button::Button5: return GLFW_MOUSE_BUTTON_5;
			case Button::Button6: return GLFW_MOUSE_BUTTON_6;
			case Button::Button7: return GLFW_MOUSE_BUTTON_7;
			case Button::Button8: return GLFW_MOUSE_BUTTON_8;
			default:
				LITHE_CORE_WARN("Unknown mouse button!");
				break;
			}
		}

		static Button FromGlfwKey()

	};

}
