#include "LayerStack.hpp"

namespace Lithe
{
	void LayerStack::PushLayer(const LayerPtr& layer)
	{
		layer->OnAttach();
		layers_.insert(layers_.begin() + (layerInsertIndex_++), layer);
	}

	void LayerStack::PushOverlay(const LayerPtr& layer)
	{
		layer->OnAttach();
		layers_.push_back(layer);
	}

	void LayerStack::PopLayer(LayerPtr layer)
	{
		auto result{ std::find(layers_.begin(), layers_.begin() + layerInsertIndex_, layer) };
		if (result != layers_.end())
		{
			(*result)->OnDetach();
			layers_.erase(result);
			layerInsertIndex_--;
		}
	}

	void LayerStack::PopOverlay(LayerPtr overlay)
	{
		auto result{ std::find(layers_.begin() + layerInsertIndex_, layers_.end(), overlay) };
		if (result != layers_.end())
		{
			(*result)->OnDetach();
			layers_.erase(result);
		}
	}
}
