#include "ltpch.h"
#include "LayerStack.hpp"

namespace Lithe
{
	void LayerStack::PushLayer(const LayerPtr& layer)
	{
		layer->OnAttach();
		m_Layers.insert(m_Layers.begin() + (m_LayerInsertIndex++), layer);
	}

	void LayerStack::PushOverlay(const LayerPtr& layer)
	{
		layer->OnAttach();
		m_Layers.push_back(layer);
	}

	void LayerStack::PopLayer(LayerPtr layer)
	{
		auto result{ std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer) };
		if (result != m_Layers.end())
		{
			(*result)->OnDetach();
			m_Layers.erase(result);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(LayerPtr overlay)
	{
		auto result{ std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay) };
		if (result != m_Layers.end())
		{
			(*result)->OnDetach();
			m_Layers.erase(result);
		}
	}
}
