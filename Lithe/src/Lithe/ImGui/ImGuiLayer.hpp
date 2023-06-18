#pragma once
#include "Lithe/Core/Layer.hpp"


namespace Lithe
{
	class LITHE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnEvent(Event& event) override;
		void OnUpdate() override;
		void OnAttach() override;
		void OnDetach() override;
	private:
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);


		float m_Time;
	};
}
