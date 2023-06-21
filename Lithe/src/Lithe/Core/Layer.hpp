/*****************************************************************//**
 * @file   Layer.hpp
 * @brief  Layer class header
 * 
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/

#pragma once
#include "Lithe/Events/Events.hpp"

namespace Lithe
{
	/**
	 * @brief Base class for all layers, such as ui/overlays and game world objects.
	 * User can create own layers by implementing this class.
	 */
	class LITHE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate() {}
		virtual void OnImGuiDraw() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}


	protected:
		std::string m_DebugName;
	};

}
