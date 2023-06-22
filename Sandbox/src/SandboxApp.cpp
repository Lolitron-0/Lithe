#include <Lithe.hpp>
#include <glm/vec2.hpp>
#include <ImGui/imgui.h>

class MyLayer : public Lithe::Layer
{
public:
    MyLayer()
        :Lithe::Layer("MyLayer")
    {}

    void OnImGuiDraw() override
    {
        static bool show = true;

        ImGui::Begin("window", &show);
        ImGui::Text("bruh");
        ImGui::End();
    }
};

class Sandbox : public Lithe::Application
{
public:
    Sandbox()
    {
        Lithe::Ref<MyLayer> myLayer{std::make_shared<MyLayer>()};
        this->PushLayer(myLayer);
    }

    ~Sandbox()
    {

    }
};

Lithe::Application* Lithe::CreateApplication()
{
    return new Sandbox();
}