#include <Lithe.hpp>

class MyLayer : public Lithe::Layer
{
public:
	MyLayer()
		:Lithe::Layer("MyLayer")
	{}

	virtual void OnEvent(Lithe::Event& event) override
	{
	}

	virtual void OnUpdate() override
	{
	}

	virtual void OnAttach() override
	{
	}
	virtual void OnDetach() override
	{
	}
};

class Sandbox : public Lithe::Application 
{
public:
	Sandbox()
	{
		this->PushLayer<MyLayer>();
		this->PushLayer<Lithe::ImGuiLayer>();
	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}