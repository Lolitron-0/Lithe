#include <Lithe.hpp>

class Sandbox : public Lithe::Application 
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lithe::Application* Lithe::CreateApplication()
{
	return new Sandbox();
}