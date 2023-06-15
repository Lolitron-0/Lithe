#pragma once
#include "Lithe/Core/Layer.hpp"


namespace Lithe
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnEvent(Event& event) override;
		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;

	private:

	};
}
