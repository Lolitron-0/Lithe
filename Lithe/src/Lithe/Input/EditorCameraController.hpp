#pragma once
#include "CameraController.hpp"

namespace Lithe
{
    // @todo editable key bindings
    class EditorCameraController : public CameraController<EditorCameraController>
    {
    public:
        EditorCameraController(const Entity& camera);

        void OnUpdate(const Timestep& ts) override;

        bool OnMouseScrolled(MouseScrolledEvent&) override;

        void Focus(const Vec3& point);

    private:
        constexpr float ZoomSpeed();
        void MousePan_(const Vec2& delta);
        void MouseRotate_(const Vec2& delta);
        void MouseZoom_(float delta);
        void UpdateTransform_();

        Vec3 m_FocalPoint;
        float m_Distance;
        Vec2 m_LastMousePos{ -1.f };
        Vec2 m_MoveSpeed{ .04f };
        float m_MouseSensitivity{  17.f };
    };

}