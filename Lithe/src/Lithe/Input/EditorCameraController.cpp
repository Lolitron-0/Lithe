#include "ltpch.h"
#include "Lithe/Core/Application.hpp"
#include "EditorCameraController.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Lithe
{

    EditorCameraController::EditorCameraController(const Entity& camera)
        :CameraController{ camera }, m_FocalPoint{ 0.f }, m_Distance{ 4.f }
    {
        m_Transform->SetRotation({ -45.f, 45.f, 0 });
        UpdateTransform_();
    }

    void EditorCameraController::OnUpdate(const Timestep& ts)
    {
        PROFILER_SCOPE("EditorCameraController::OnUpdate()");
        if (Keyboard::IsKeyPressed(Keyboard::Key::LeftAlt))
        {
            //Application::GetInstance().GetWindow().HideCursor();
            auto mousePos = Mouse::GetPosition();
            auto delta = m_LastMousePos.x != -1 ? (m_LastMousePos - mousePos) * (float)ts : Vec2{ 0.f, 0.f };
            m_LastMousePos = mousePos;

            if (Mouse::IsButtonPressed(Mouse::Button::Left))
                MouseRotate_(delta);
            if (Mouse::IsButtonPressed(Mouse::Button::Middle))
                MousePan_(delta);
            if (Mouse::IsButtonPressed(Mouse::Button::Right))
                MouseZoom_(delta.x);

            UpdateTransform_();
        }
        /*else if (Application::GetInstance().GetWindow().IsCursorHidden())
            Application::GetInstance().GetWindow().ShowCursor();*/
    }

    bool EditorCameraController::OnMouseScrolled(MouseScrolledEvent& event)
    {
        if (Keyboard::IsKeyPressed(Keyboard::Key::LeftAlt))
        {
            m_Distance += -event.GetOffsetY() * ZoomSpeed() * 0.5f;
            if (m_Distance < 1.f)
            {
                m_FocalPoint += m_Transform->GetFront();
                m_Distance = 1.f;
            }
        }
        return false;
    }

    void EditorCameraController::Focus(const Vec3& point)
    {
        m_FocalPoint = point;
        m_Distance = 4.f;
        UpdateTransform_();
    }

    constexpr float EditorCameraController::ZoomSpeed()
    {
        auto distance = std::max(m_Distance, 0.001f);
        return std::min((float)glm::pow(distance, 1.5) * 0.1f, 100.f);
    }

    void EditorCameraController::MousePan_(const Vec2& delta)
    {
        m_FocalPoint += m_Transform->GetRight() * delta.x * m_MoveSpeed.x * m_Distance;
        m_FocalPoint += -m_Transform->GetUp() * delta.y * m_MoveSpeed.y * m_Distance;
    }

    void EditorCameraController::MouseRotate_(const Vec2& delta)
    {
        m_Transform->Rotate({ delta.y * m_MouseSensitivity, delta.x * m_MouseSensitivity, 0.f });
    }

    void EditorCameraController::MouseZoom_(float delta)
    {
        m_Distance += delta * ZoomSpeed();
        if (m_Distance < 1.f)
        {
            m_FocalPoint += m_Transform->GetFront();
            m_Distance = 1.f;
        }
    }

    void EditorCameraController::UpdateTransform_()
    {
        m_Transform->SetPosition(m_FocalPoint - m_Transform->GetFront() * m_Distance);
    }

}