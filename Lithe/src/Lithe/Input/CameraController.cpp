#include "ltpch.h"
#include "CameraController.hpp"
#include "Inputs.hpp"

namespace Lithe
{

    /************************************************************************/
    /* Fly camera controller                                                */
    /************************************************************************/

    void FlyCameraController::OnUpdate(const Timestep& ts)
    {
        auto fpsScale = static_cast<float>(ts.GetFpsScale());
        if (Keyboard::IsKeyPressed(Keyboard::Key::W))
            m_Camera->ShiftPosition(Ra::CameraDirection::Forward, m_FlySpeed * fpsScale);
        if (Keyboard::IsKeyPressed(Keyboard::Key::A))
            m_Camera->ShiftPosition(Ra::CameraDirection::Left, m_FlySpeed * fpsScale);
        if (Keyboard::IsKeyPressed(Keyboard::Key::S))
            m_Camera->ShiftPosition(Ra::CameraDirection::Backward, m_FlySpeed * fpsScale);
        if (Keyboard::IsKeyPressed(Keyboard::Key::D))
            m_Camera->ShiftPosition(Ra::CameraDirection::Right, m_FlySpeed * fpsScale);
        if (Keyboard::IsKeyPressed(Keyboard::Key::Q))
            m_Camera->ShiftPosition(Ra::CameraDirection::Down, m_FlySpeed * fpsScale);
        if (Keyboard::IsKeyPressed(Keyboard::Key::E))
            m_Camera->ShiftPosition(Ra::CameraDirection::Up, m_FlySpeed * fpsScale);
    }

    bool FlyCameraController::OnMouseMoved(MouseMovedEvent& event)
    {
        auto xOffset = m_LastMouseX == -1 ? 0.f : event.GetMouseX() - m_LastMouseX;
        auto yOffset = m_LastMouseY == -1 ? 0.f :  m_LastMouseY - event.GetMouseY();

        m_Camera->ShiftYaw(xOffset * m_MouseSensitivity);
        m_Camera->ShiftPitch(yOffset * m_MouseSensitivity);

        if (m_Camera->GetPitch() > 89.f)
            m_Camera->SetPitch(89.f);   
        
        if (m_Camera->GetPitch() < -89.f)
            m_Camera->SetPitch(-89.f);

        m_LastMouseX = event.GetMouseX();
        m_LastMouseY = event.GetMouseY();

        return false;
    }

}