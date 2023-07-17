#include "EditorLayer.hpp"
#include "EditorConfig.hpp"
#include <imgui.h>

namespace Lithe
{

    int p_ChosenGizmoMode = 0;

    EditorLayer::EditorLayer() :Layer("EditorLayer")
    {
        m_Texture = Ra::Texture::Create();
        m_Texture->LoadFromFile(R"(assets\container2.png)");
        Ref<Ra::Texture> spec = Ra::Texture::Create();
        spec->LoadFromFile(R"(assets\container2_specular.png)");
        m_Material.DiffuseMap = m_Texture;
        m_Material.SpecularMap = spec;

        Ra::FramebufferProperties props;
        props.Width = Application::GetInstance().GetWindow().GetWidth();
        props.Height = Application::GetInstance().GetWindow().GetHeight();
        props.Attachments = { Ra::TextureFormat::Color, Ra::TextureFormat::R32, Ra::TextureFormat::Depth };
        props.Samples = 1;
        m_Framebuffer = Ra::Framebuffer::Create(props);

        m_CurrentScene = MakeRef<Scene>();

        m_Cube = m_CurrentScene->CreateEntity("Cube");
        m_Cube.AddComponent<MeshRendererComponent>(Ra::Renderer::Storage.CubeVertexArray, m_Material);

        m_Lamp = m_CurrentScene->CreateEntity("Point light");
        m_Lamp.AddComponent<PointLightComponent>();
        m_Lamp.GetComponent<TransformComponent>().SetPosition({ 1.5,1.5,1.5 });

        m_EditorCamera = m_CurrentScene->CreateEntity("Editor Camera");
        auto cam = MakeRef<PerspectiveCamera>(45.f, 16.f / 9.f);
        m_EditorCamera.AddComponent<CameraComponent>(cam, true);

        m_CameraController = MakeRef<EditorCameraController>(m_EditorCamera);

        // Panels
        m_SceneHierarchyPanel.SetTrackScene(m_CurrentScene);
    }

    void EditorLayer::OnEvent(Event& event)
    {
        m_CameraController->OnEvent(event);
        EventDispatcher dispatcher{ event };
        dispatcher.Dispatch<KeyPressedEvent>(LT_BIND_EVENT_FN(OnKeyPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& event)
    {
        auto key = event.GetKeyCode();
        if (key == EditorConfig::GetOperationKey(KeybindOperations::GizmoModeTranslate))
        {
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            p_ChosenGizmoMode = 0;
        }
        else if (key == EditorConfig::GetOperationKey(KeybindOperations::GizmoModeRotate))
        {
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::ROTATE;
            p_ChosenGizmoMode = 1;
        }
        else if (key == EditorConfig::GetOperationKey(KeybindOperations::GizmoModeScale))
        {
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::SCALE;
            p_ChosenGizmoMode = 2;
        }
        else if (key == EditorConfig::GetOperationKey(KeybindOperations::GizmoModeUniversal))
        {
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::UNIVERSAL;
            p_ChosenGizmoMode = 3;
        }

        if (key == EditorConfig::GetOperationKey(KeybindOperations::Focus))
        {
            auto selection = m_CurrentScene->GetSelectedEntity();
            m_CameraController->Focus(selection ? selection.GetComponent<TransformComponent>().GetPosition() : Vec3{ 0.f });
        }

        return false;
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

        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float defaultMinWindowWidth = style.WindowMinSize.x;
        style.WindowMinSize.x = 370.f;
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        style.WindowMinSize.x = defaultMinWindowWidth;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", nullptr, false, &show != nullptr))
                    Application::GetInstance().Close();
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window"))
            {
                if (ImGui::MenuItem("Viewport", nullptr, &p_ViewportOpen))
                    p_ViewportOpen = true;
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();

        // VIewport
        if (p_ViewportOpen)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0,0 });
            ImGui::Begin("Viewport", &p_ViewportOpen);
            HOVER_FOCUS();

            m_ViewportFocused = ImGui::IsWindowFocused();
            Application::GetInstance().GetImGuiLayer()->BlockEvents(!m_ViewportFocused);

            auto winPos = ImGui::GetWindowPos();
            auto viewportPanelSize = ImGui::GetWindowSize();

            m_ViewportBounds[0] = Vec2{ ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y };
            m_ViewportBounds[1] = Vec2{ m_ViewportBounds[0].x + viewportPanelSize.x, m_ViewportBounds[0].y + viewportPanelSize.y };

            if (m_ViewportSize != *(glm::vec2*)&viewportPanelSize) // haha 
            {
                m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                m_CurrentScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            }

            auto textureId = m_Framebuffer->GetDrawTextureHandle();
            ImGui::GetCurrentWindow()->DrawList->AddImage((ImTextureID)(std::uintptr_t)textureId,
                { m_ViewportBounds[0].x, m_ViewportBounds[0].y },
                { m_ViewportBounds[1].x, m_ViewportBounds[1].y }, { 0,1 }, { 1,0 });


            // Gizmo
            DrawGizmoControls_();
            DrawGizmo_();

            ImGui::End();
            ImGui::PopStyleVar();
        }

        // Panels
        m_SceneHierarchyPanel.OnImGuiDraw();


        // Stats
        ImGui::Begin("Renderer stats");
        auto stats = Ra::Renderer::GetStats();
        ImGui::LabelText("Draw calls", std::to_string(stats.DrawCalls).c_str());
        ImGui::LabelText("Indices", std::to_string(stats.Indices).c_str());
        ImGui::End();

    }

    void EditorLayer::OnUpdate(const Lithe::Timestep& ts)
    {
        m_CameraController->OnUpdate(ts);

        m_Framebuffer->StartWriting();

        Ra::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
        Ra::RenderCommand::Clear();

        m_CurrentScene->OnUpdate(ts);

        // Mouse picking
        auto [mouseLocX, mouseLocY] = ImGui::GetMousePos();
        mouseLocX -= m_ViewportBounds[0].x;
        mouseLocY -= m_ViewportBounds[0].y;
        LITHE_CORE_LOG_DEBUG("{0}", m_Framebuffer->ReadPixel(1, mouseLocX, mouseLocY));

        m_Framebuffer->StopWriting();
    }

    void EditorLayer::OnAttach()
    {
        EditorConfig::Init();
    }

    void EditorLayer::DrawGizmo_()
    {
        auto selectedEntity = m_CurrentScene->GetSelectedEntity();
        if (selectedEntity)
        {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();
            auto winPos = ImGui::GetWindowPos();
            auto winWidth = ImGui::GetWindowWidth();
            auto winHeight = ImGui::GetWindowHeight();
            ImGuizmo::SetRect(winPos.x, winPos.y, winWidth, winHeight);

            auto cameraEntity = m_CurrentScene->GetPrimaryCameraEntity();
            const auto& camera = cameraEntity.GetComponent<CameraComponent>();
            Mat4 cameraView = Inverse(cameraEntity.GetComponent<TransformComponent>().GetMatrix());
            const Mat4& cameraProjection = camera.Camera->GetProjection();

            auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();
            Mat4 transform = transformComponent.GetMatrix();

            bool snap = Keyboard::IsKeyPressed(EditorConfig::GetOperationKey(KeybindOperations::HoldGizmoSnap));
            ImGuizmo::Manipulate(&cameraView[0][0],
                &cameraProjection[0][0],
                m_CurrentGizmoOperation,
                m_CurrentGizmoMode,
                &transform[0][0], nullptr, snap ? EditorConfig::GetGizmoSnap(m_CurrentGizmoOperation) : nullptr
            );

            if (ImGuizmo::IsUsing())
            {
                Vec3 translation{ 0.f }, scale{ 0.f }, rotation{ 0.f };
                if (DecomposeMatrix(transform, translation, rotation, scale)) {
                    transformComponent.SetPosition(translation);
                    transformComponent.SetRotation(rotation);
                    transformComponent.SetScale(scale);
                }
            }

        }
    }

#define HANDLE_AXIS_LOCK(operation) \
if (lock == 1)\
    m_CurrentGizmoOperation = ImGuizmo::OPERATION::##operation##_X;\
else if (lock == 2)\
    m_CurrentGizmoOperation = ImGuizmo::OPERATION::##operation##_Y;\
else if (lock == 3)\
    m_CurrentGizmoOperation = ImGuizmo::OPERATION::##operation##_Z;\

    void EditorLayer::DrawGizmoControls_()
    {
        ImVec2 controlsWindowPadding = { 25, 70 };

        static bool vals[] = { true, false, false, false };
        static ImTextureID textureIds[] =
        {
            (ImTextureID)(std::uintptr_t)EditorConfig::TranslateIcon->GetNativeTerxtureHandle(),
            (ImTextureID)(std::uintptr_t)EditorConfig::RotateIcon->GetNativeTerxtureHandle(),
            (ImTextureID)(std::uintptr_t)EditorConfig::ScaleIcon->GetNativeTerxtureHandle(),
            (ImTextureID)(std::uintptr_t)EditorConfig::UniTransformIcon->GetNativeTerxtureHandle()
        };
        EditorConfig::DrawToggleImageList(textureIds, vals, &p_ChosenGizmoMode, (std::size_t)4, { 30.f, 30.f }, controlsWindowPadding);
        int lock = 0;
        if (Keyboard::IsKeyPressed(EditorConfig::GetOperationKey(KeybindOperations::HoldGizmoLockX)))
            lock = 1;
        else if (Keyboard::IsKeyPressed(EditorConfig::GetOperationKey(KeybindOperations::HoldGizmoLockY)))
            lock = 2;
        else if (Keyboard::IsKeyPressed(EditorConfig::GetOperationKey(KeybindOperations::HoldGizmoLockZ)))
            lock = 3;

        switch (p_ChosenGizmoMode)
        {
        case 0:
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
            HANDLE_AXIS_LOCK(TRANSLATE);
            break;
        case 1:
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::ROTATE;
            HANDLE_AXIS_LOCK(ROTATE);
            break;
        case 2:
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::SCALE;
            HANDLE_AXIS_LOCK(SCALE);
            break;
        case 3:
            m_CurrentGizmoOperation = ImGuizmo::OPERATION::UNIVERSAL;
            break;
        default:
            break;
        }

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + controlsWindowPadding.x);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 50);
        static bool globalToggled = false;
        if (EditorConfig::DrawToggleImageButton((ImTextureID)(std::uintptr_t)EditorConfig::GlobalIconMin->GetNativeTerxtureHandle(), &globalToggled, { 30,30 }))
            m_CurrentGizmoMode = globalToggled ? ImGuizmo::MODE::WORLD : ImGuizmo::MODE::LOCAL;

    }

}