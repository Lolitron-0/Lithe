#include <Lithe.hpp>

class MyLayer : public Lithe::Layer
{
public:
	MyLayer()
		:Lithe::Layer("MyLayer")
	{}

	virtual void OnEvent(Lithe::Event& event) override
	{
		LITHE_TRACE(event);
	}

	virtual void OnUpdate() override
	{
	}
};

class Sandbox : public Lithe::Application 
{
public:
	Sandbox()
	{
		this->PushLayer<MyLayer>();
	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}