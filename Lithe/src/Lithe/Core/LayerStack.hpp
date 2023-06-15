/*****************************************************************//**
 * @file   LayerStack.hpp
 * @brief  LayerStack header file
 *
 * @author Lolitron
 * @date   June 2023
 *********************************************************************/
#pragma once
#include "Base.hpp"
#include "Layer.hpp"
#include <vector>

namespace Lithe
{
	/// Alias for smart pointer type which is holding Layer objects
	using LayerPtr = std::shared_ptr<Layer>;

	/**
	 * @brief Class for layer creation and storage.
	 * First half of the stack is game world layers, second contains ui/overlay layers.
	 * Stack is used to render content in proper order and propagete events correctly.
	 */
	class LITHE_API LayerStack
	{
	public:
		using LayerBuffer = std::vector<LayerPtr>;

		LayerStack() = default;

		/**
		 * @brief Adds game world layer to stack
		 * @note It's recommended to use this method for reinsertion (after popping existing layer). Add new layers with PushLayer<T>(Args&&...)
		 * @param layer Pointer to push
		*/
		void PushLayer(const LayerPtr& layer);

		/**
		 * @brief Adds ui layer to stack
		 * @note It's recommended to use this method for reinsertion (after popping existing layer). Add new layers with PushLayer<T>(Args&&...)
		 * @param layer Pointer to push
		*/
		void PushOverlay(const LayerPtr& layer);

		/**
		 * @brief Method for pushing a game world layer onto stack
		 * @param ...args Arguments for Layer constructor
		 *
		 * @return Pointer object to a created layer. It can be used to access the layer or to pop it later
		 */
		template <class T, class... Args>
		LayerPtr PushLayer(Args&&... args)
		{
			auto ptr{ std::make_shared<T>(std::forward<Args>(args)...) };
			PushLayer(ptr);
			return ptr;
		}

		/**
		 * @brief Method for pushing a ui/overlay layer onto stack
		 * @param ...args Arguments for Layer constructor
		 *
		 * @return Pointer object to a created layer. It can be used to access the layer or to pop it later
		 */
		template <class T, class... Args>
		LayerPtr PushOverlay(Args&&... args)
		{
			auto ptr{ std::make_shared<T>(std::forward<Args>(args)...) };
			PushOverlay(ptr);
			return ptr;
		}

		/**
		 * @brief Deletes game world layer from stack.
		 *
		 * @param layer Layer to pop
		 */
		void PopLayer(LayerPtr layer);

		/**
		* @brief Deletes ui layer from stack.
		*
		* @param overlay Layer to pop
		*/
		void PopOverlay(LayerPtr overlay);

		//-------------- Overloads for range-based loops

		LayerBuffer::iterator begin() { return layers_.begin(); }
		LayerBuffer::iterator end() { return layers_.end(); }
		LayerBuffer::reverse_iterator rbegin() { return layers_.rbegin(); }
		LayerBuffer::reverse_iterator rend() { return layers_.rend(); }

		LayerBuffer::const_iterator begin() const { return layers_.begin(); }
		LayerBuffer::const_iterator end() const { return layers_.cend(); }
		LayerBuffer::const_reverse_iterator rbegin() const { return layers_.rbegin(); }
		LayerBuffer::const_reverse_iterator rend() const { return layers_.rend(); }

		//--------------

	private:

		unsigned int layerInsertIndex_{ 0 };
		LayerBuffer layers_;
	};

}

