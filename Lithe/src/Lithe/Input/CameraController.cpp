#include "ltpch.h"
#include "CameraController.hpp"
#include "Inputs.hpp"

namespace Lithe
{
    CameraController::CameraController(const Ra::Camera& camera)
    {
        m_Camera = std::make_unique<Ra::Camera>(camera);
    }

    /************************************************************************/
    /* Fly camera controller                                                */
    /************************************************************************/

    void FlyCameraController::OnUpdate()
    {
        if (Keyboard::IsKeyPressed(Keyboard::Key::W))
            m_Camera->ShiftPosition(Ra::CameraDirection::Forward, .01f);
        if (Keyboard::IsKeyPressed(Keyboard::Key::A))
            m_Camera->ShiftPosition(Ra::CameraDirection::Left, .01f);
        if (Keyboard::IsKeyPressed(Keyboard::Key::S))
            m_Camera->ShiftPosition(Ra::CameraDirection::Backward, .01f);
        if (Keyboard::IsKeyPressed(Keyboard::Key::D))
            m_Camera->ShiftPosition(Ra::CameraDirection::Right, .01f);
        if (Keyboard::IsKeyPressed(Keyboard::Key::Q))
            m_Camera->ShiftPosition(Ra::CameraDirection::Down, .01f);
        if (Keyboard::IsKeyPressed(Keyboard::Key::E))
            m_Camera->ShiftPosition(Ra::CameraDirection::Up, .01f);
    }

    bool FlyCameraController::OnMouseMoved(MouseMovedEvent& event)
    {
        auto xOffset = m_LastMouseX == -1 ? 0.f : event.GetMouseX() - m_LastMouseX;
        auto yOffset = m_LastMouseY == -1 ? 0.f :  m_LastMouseY - event.GetMouseY();

        m_Camera->ShiftYaw(xOffset * .1f);
        m_Camera->ShiftPitch(yOffset * .1f);

        if (m_Camera->GetPitch() > 89.f)
            m_Camera->SetPitch(89.f);   
        
        if (m_Camera->GetPitch() < -89.f)
            m_Camera->SetPitch(-89.f);

        m_LastMouseX = event.GetMouseX();
        m_LastMouseY = event.GetMouseY();

        return false;
    }

    void FlyCameraController::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseMovedEvent>(LT_BIND_EVENT_FN(FlyCameraController::OnMouseMoved));
    }

}