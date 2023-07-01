/*****************************************************************//**
 * @file   Layer.hpp
 * @brief  Layer class header
 * 
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/

#pragma once
#include "Lithe/Events/Events.hpp"
#include "Timestep.hpp"

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
		virtual void OnUpdate(const Timestep& ts) {}
		virtual void OnImGuiDraw() {}

		/// Called whet this Layer is pushed to LayerStack
		virtual void OnAttach() {}
        /// Called whet this Layer is popped from LayerStack
		virtual void OnDetach() {}


	protected:
		std::string m_DebugName;
	};

}
