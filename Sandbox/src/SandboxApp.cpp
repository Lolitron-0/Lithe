#include <Lithe.hpp>

class MyLayer : public Lithe::Layer
{
public:
    MyLayer()
        :Lithe::Layer("MyLayer")
    {}

    virtual void OnEvent(Lithe::Event& event) override
    {
        if (event.IsInCategory(Lithe::EventCategoryKeyboard))
            LITHE_DEBUG(Lithe::Keyboard::IsKeyPressed(Lithe::Keyboard::Key::A));
    }

    bool OnKeyPressed(Lithe::KeyPressedEvent& event)
    {
        //LITHE_DEBUG(event);
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