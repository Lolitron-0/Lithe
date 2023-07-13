#include <Lithe.hpp>

class MyLayer : public Lithe::Layer
{
public:
    MyLayer()
        :Lithe::Layer("MyLayer")
    {
        Ra::Camera cam{{0, 3, 5}, 16.f / 9.f};
        cam.ShiftPitch(-30);
        m_CameraController = std::make_shared<Lithe::RMBCaptureFlyCameraController>(cam);

        float data[] = {
            // front
            -1.0, -1.0,  1.0,
             1.0, -1.0,  1.0,
             1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // back
            -1.0, -1.0, -1.0,
             1.0, -1.0, -1.0,
             1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0
        };

        m_VertexArray = Ra::VertexArray::Create();

        m_VertexBuffer = Ra::VertexBuffer::Create(data, sizeof(data));
        Ra::BufferLayout layout = {
            {Ra::BufferDataType::Float3, "position"},
        };
        m_VertexBuffer->SetLayout(layout);

        unsigned int indices[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
        };
        m_IndexBuffer = Ra::IndexBuffer::Create(indices, 36);

        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_TestShader = Ra::Shader::Create(
            R"(G:\dev\Lithe\Lithe\src\Lithe\Core\test.vert)",
            R"(G:\dev\Lithe\Lithe\src\Lithe\Core\test.frag)");

    }

    void OnEvent(Lithe::Event& event) override
    {
        m_CameraController->OnEvent(event);
    }

    void OnImGuiDraw() override
    {
        static bool show = true;

        ImGui::Begin("window", &show);
        ImGui::Text("bruh");
        ImGui::End();
    }

    void OnUpdate(const Lithe::Timestep& ts) override
    {
        m_CameraController->OnUpdate(ts);

        Ra::RenderCommand::SetClearColor({ 1.f, 0.f, 1.f, 0.f });
        Ra::RenderCommand::Clear();

    }



private:
    Lithe::Ref<Ra::Shader> m_TestShader;
    Lithe::Ref<Ra::VertexBuffer> m_VertexBuffer;
    Lithe::Ref<Ra::IndexBuffer> m_IndexBuffer;
    Lithe::Ref<Ra::VertexArray> m_VertexArray;
    Lithe::Ref<Lithe::RMBCaptureFlyCameraController> m_CameraController;
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