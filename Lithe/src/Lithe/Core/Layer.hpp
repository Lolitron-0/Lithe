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

		virtual void OnEvent(Event& event) = 0;
		virtual void OnUpdate() = 0;
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;


	protected:
		std::string m_DebugName;
	};

}
