#include "EditorLayer.hpp"

namespace Lithe
{

    EditorLayer::EditorLayer() :Layer("EditorLayer")
    {
        m_Texture = Ra::Texture::Create();
        m_Texture->LoadFromFile(R"(assets\container2.png)");
        m_Material.DiffuseMap = m_Texture;
        m_Material.Transparency = 0.8;

        Ra::FramebufferProperties props;
        props.Width = Application::GetInstance().GetWindow().GetWidth();
        props.Height = Application::GetInstance().GetWindow().GetHeight();
        props.Attachments = { Ra::TextureFormat::Color, Ra::TextureFormat::Depth };
        props.Samples = 8;
        m_Framebuffer = Ra::Framebuffer::Create(props);

        m_CurrentScene = std::make_shared<Scene>();

        m_Cube = m_CurrentScene->CreateEntity();
        m_Cube.AddComponent<MeshRendererComponent>(m_Material);

        m_EditorCamera = m_CurrentScene->CreateEntity("Editor Camera");
        auto cam = std::make_shared<PerspectiveCamera>(45.f, 16.f / 9.f);
        m_EditorCamera.AddComponent<CameraComponent>(cam, true);

        m_CameraController = std::make_shared<Lithe::RMBCaptureFlyCameraController>(m_EditorCamera);
        m_CameraController->GetTransform().SetPosition({0, 2, 2});
        m_CameraController->GetTransform().RotateY(-45);
    }

    void EditorLayer::OnEvent(Event& event)
    {
        m_CameraController->OnEvent(event);
    }

    void EditorLayer::OnImGuiDraw()
    {
        static bool show = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool p_ViewportOpen = true;
        static float rot[] = { 0,0,0 };
        static float fov = 45.f;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &show, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);


        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", NULL, false, &show != NULL))
                    Application::GetInstance().Close();            
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Viewport"))
                    p_ViewportOpen = true;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
        if (p_ViewportOpen) {
            ImGui::Begin("Viewport", &p_ViewportOpen);

            auto viewportPanelSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *(glm::vec2*)&viewportPanelSize) // haha type punning goes brr
            {
                m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                m_CurrentScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            }
            auto textureId = m_Framebuffer->GetDrawTextureHandle();
            ImGui::Image(reinterpret_cast<void*>((std::uintptr_t)textureId), ImVec2{
                static_cast<float>(m_Framebuffer->GetProperties().Width),
                static_cast<float>(m_Framebuffer->GetProperties().Height) },
                ImVec2{ 0,1 }, ImVec2{ 1,0 });

            ImGui::End();
        }
        ImGui::PopStyleVar();

        ImGui::Begin("Settings");
        if (ImGui::DragFloat3("Rotation", rot, 1, -360, 360))
            m_Cube.GetComponent<TransformComponent>().SetRotation(Vec3{rot[0],rot[1], rot[2]});
        if (ImGui::DragFloat("FOV", &fov, 1, 30, 170))
        {
            auto props = m_CameraController->GetCamera()->GetCameraProperties<PerspectiveCameraProperties>();
            props.Fov = fov;
            m_CameraController->GetCamera()->SetCameraProperties(props);
        }
        ImGui::End();
    }

    void EditorLayer::OnUpdate(const Lithe::Timestep& ts)
    {
        m_CameraController->OnUpdate(ts);

        m_Framebuffer->StartWriting();

        Ra::RenderCommand::SetClearColor({ 1.f, 1.f, 1.f, 0.1f });
        Ra::RenderCommand::Clear();

        auto& trans = m_Cube.GetComponent<TransformComponent>();
        //trans.RotateX(100.f * ts);
        m_CurrentScene->OnUpdate(ts); 

        m_Framebuffer->StopWriting();
    }

    void EditorLayer::OnAttach()
    {
    }

}