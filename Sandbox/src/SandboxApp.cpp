#include <Lithe.hpp>
#include <glm/vec2.hpp>

class MyLayer : public Lithe::Layer
{
public:
    MyLayer()
        :Lithe::Layer("MyLayer")
    {}

    virtual void OnEvent(Lithe::Event& event) override
    {
    }

    bool OnKeyPressed(Lithe::KeyPressedEvent& event)
    {
    }

    virtual void OnUpdate() override
    {
    }

    virtual void OnAttach() override
    {
        glm::vec2 v{1, 2.5};
        LITHE_DEBUG(v);
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
        this->PushOverlay<Lithe::ImGuiLayer>();
    }

    ~Sandbox()
    {

    }
};

Lithe::Application* Lithe::CreateApplication()
{
    return new Sandbox();
}