#include "LayerStack.hpp"

namespace Lithe
{
	void LayerStack::PopLayer(LayerPtr layer)
	{
		auto result = std::find(layers_.begin(), layers_.begin()+layerInsertIndex_, layer);
		if (result != layers_.end())
		{
			layers_.erase(result);
			layerInsertIndex_--;
		}
	}

	void LayerStack::PopOverlay(LayerPtr overlay)
	{
		auto result = std::find(layers_.begin() + layerInsertIndex_, layers_.end(), overlay);
		if (result != layers_.end())
		{
			layers_.erase(result);
		}
	}
}
