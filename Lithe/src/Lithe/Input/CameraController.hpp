#pragma once
#include <RenderAbstraction.hpp>
#include "Lithe/Events/Events.hpp"

namespace Lithe
{
    class CameraController
    {
    public:
        CameraController(const Ra::Camera& camera);
        virtual ~CameraController() = default;

        virtual void OnEvent(Event& event) = 0;
        virtual void OnUpdate() {}
        virtual bool OnKeyPressed(KeyPressedEvent& event) { return false; };
        virtual bool OnKeyReleased(KeyReleasedEvent& event) { return false; };
        virtual bool OnMouseMoved(MouseMovedEvent&) { return false; };
        virtual bool OnMouseScrolled(MouseScrolledEvent&) { return false; };

        Ra::Camera& GetCamera() { return *m_Camera; }

    protected:
        Scope<Ra::Camera> m_Camera;
    };

    /************************************************************************/
    /* Fly Camera                                                           */
    /************************************************************************/


    class FlyCameraController : public CameraController
    {
    public:
        FlyCameraController(const Ra::Camera& camera)
            :CameraController(camera)
        {}

        void OnUpdate() override;

        bool OnMouseMoved(MouseMovedEvent&) override;

        void OnEvent(Event& event) override;

    private:
        float m_LastMouseX{ -1 };
        float m_LastMouseY{ -1 };
    };

}