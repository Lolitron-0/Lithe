#include "ltpch.h"
#include "CameraController.hpp"
#include "Inputs.hpp"
#include "Lithe/Core/Application.hpp"

namespace Lithe
{
    /************************************************************************/
    /* RMB Fly camera controller                                            */
    /************************************************************************/

    RMBCaptureFlyCameraController::RMBCaptureFlyCameraController(const Ra::Camera& camera)
        :FlyCameraControllerImpl(camera)
    {
        Application::GetInstance().GetWindow().ShowCursor();
    }

    void RMBCaptureFlyCameraController::OnUpdate(const Timestep& ts)
    {
        if (m_Captured)
            Base::OnUpdate(ts);
    }

    bool RMBCaptureFlyCameraController::OnMouseMoved(MouseMovedEvent& event)
    {
        if (m_Captured)
            Base::OnMouseMoved(event);

        m_LastMousePos.x = event.GetMouseX();
        m_LastMousePos.y = event.GetMouseY();
        return false;
    }

    bool RMBCaptureFlyCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& event)
    {
        m_Captured = event.GetMouseButton() == Mouse::Button::Right;
        auto& window = Application::GetInstance().GetWindow();
        if (m_Captured && !window.IsCursorHidden())
            window.HideCursor();
        return false;
    }

    bool RMBCaptureFlyCameraController::OnMouseButtonReleased(MouseButtonReleasedEvent&)
    {
        m_Captured = false;
        Application::GetInstance().GetWindow().ShowCursor();
        return false;
    }

}