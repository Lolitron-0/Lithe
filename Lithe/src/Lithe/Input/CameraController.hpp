#pragma once
#include <RenderAbstraction.hpp>
#include "Lithe/Core/Timestep.hpp"
#include "Lithe/Events/Events.hpp"
#include <functional>

namespace Lithe
{
    /**
     * @brief Base class for user-defined camera controllers
     * Camera controllers are wrappers around camera object, handling user input.
     * There are a bunch of methods to optionally override, they should be called in corresponding layer methods
     * @attention OnEvent call is necessary for the event handlers to work
     * @note This class uses CRTP to dispatch events. So deriving should look like this
     * @code{.cpp}
     * class MyController : public CameraController<MyController>
     * {
     *     // ...
     * };
     * @endcode
    */
    template<class Derived>
    class CameraController
    {
    public:
        CameraController(const Ra::Camera& camera)
        {
            m_Camera = std::make_unique<Ra::Camera>(camera);
        }
        virtual ~CameraController() = default;

        virtual void OnEvent(Event& event)
        {
            EventDispatcher dispatcher{ event };
            dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Derived::OnMouseMoved, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Derived::OnKeyPressed, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Derived::OnKeyReleased, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Derived::OnMouseScrolled, static_cast<Derived*>(this), std::placeholders::_1));
        }
        virtual void OnUpdate(const Timestep& ts) {}
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

    /**
     * @brief Preset camera controller class
     * Controls are WASD for flying around and QE for ascend/descend. Mouse movement rotates the camera in yaw/pitch axis
    */
    class FlyCameraController : public CameraController<FlyCameraController>
    {
    public:
        FlyCameraController(const Ra::Camera& camera)
            :CameraController(camera)
        {}

        void OnUpdate(const Timestep& ts) override;

        bool OnMouseMoved(MouseMovedEvent&) override;

        /**
         * @brief Mouse sensitivity is a number typically in 0..1 range, but can be set to higher values
         * @return FlyController mouse sensitivity
        */
        float GetMouseSensitivity() const { return m_MouseSensitivity; }
        /**
         * @brief Mouse sensitivity is a number typically in 0..1 range, but can be set to higher values
         * @param val New sensitivity value
        */
        void SetMouseSensitivity(float val) { m_MouseSensitivity = val; }

        float GetFlySpeed() const { return m_FlySpeed; }
        void SetFlySpeed(float val) { m_FlySpeed = val; }

    private:
        float m_LastMouseX{ -1 };
        float m_LastMouseY{ -1 };

        float m_MouseSensitivity{ .1f };
        float m_FlySpeed{ 3.f };
    };

}