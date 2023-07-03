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

        void OnEvent(Event& event)
        {
            EventDispatcher dispatcher{ event };
            dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Derived::OnMouseMoved, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&Derived::OnMouseButtonPressed, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&Derived::OnMouseButtonReleased, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Derived::OnKeyPressed, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&Derived::OnKeyReleased, static_cast<Derived*>(this), std::placeholders::_1));
            dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Derived::OnMouseScrolled, static_cast<Derived*>(this), std::placeholders::_1));
        }
        virtual void OnUpdate(const Timestep& ts) {}
        virtual bool OnKeyPressed(KeyPressedEvent& event) { return false; };
        virtual bool OnKeyReleased(KeyReleasedEvent& event) { return false; };
        virtual bool OnMouseMoved(MouseMovedEvent&) { return false; };
        virtual bool OnMouseButtonPressed(MouseButtonPressedEvent&) { return false; };
        virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent&) { return false; };
        virtual bool OnMouseScrolled(MouseScrolledEvent&) { return false; };

        Ra::Camera& GetCamera() { return *m_Camera; }

    protected:
        Scope<Ra::Camera> m_Camera;
    };

    /************************************************************************/
    /* Fly Camera                                                           */
    /************************************************************************/

#include <type_traits>

    template<bool B, class T, class F>
    struct enable_ifelse { using type = T; };

    template<class T, class F>
    struct enable_ifelse<true, T, F> { using type = T; };

    /**
     * @brief Preset camera controller class
     * Controls are WASD for flying around and QE for ascend/descend. Mouse movement rotates the camera in yaw/pitch axis
    */
    template<class Derived = void>
    class FlyCameraControllerImpl : public CameraController
        <
            typename enable_ifelse< std::is_void<Derived>::value,
                FlyCameraControllerImpl<>,
                Derived>
            ::type
        >
    {
    public:
        FlyCameraControllerImpl(const Ra::Camera& camera)
            :CameraController(camera)
        {}

        virtual void OnUpdate(const Timestep& ts) override
        {
            if (Keyboard::IsKeyPressed(Keyboard::Key::W))
                m_Camera->ShiftPosition(Ra::CameraDirection::Forward, m_FlySpeed * (float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::A))
                m_Camera->ShiftPosition(Ra::CameraDirection::Left, m_FlySpeed * (float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::S))
                m_Camera->ShiftPosition(Ra::CameraDirection::Backward, m_FlySpeed * (float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::D))
                m_Camera->ShiftPosition(Ra::CameraDirection::Right, m_FlySpeed * (float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::Q))
                m_Camera->ShiftPosition(Ra::CameraDirection::Down, m_FlySpeed * (float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::E))
                m_Camera->ShiftPosition(Ra::CameraDirection::Up, m_FlySpeed * (float)ts);
        }

        virtual bool OnMouseMoved(MouseMovedEvent& event) override
        {
            auto xOffset = m_LastMousePos.x == -1 ? 0.f : event.GetMouseX() - m_LastMousePos.x;
            auto yOffset = m_LastMousePos.y == -1 ? 0.f : m_LastMousePos.y - event.GetMouseY();

            m_Camera->ShiftYaw(xOffset * m_MouseSensitivity);
            m_Camera->ShiftPitch(yOffset * m_MouseSensitivity);

            if (m_Camera->GetPitch() > 89.f)
                m_Camera->SetPitch(89.f);

            if (m_Camera->GetPitch() < -89.f)
                m_Camera->SetPitch(-89.f);

            m_LastMousePos.x = event.GetMouseX();
            m_LastMousePos.y = event.GetMouseY();

            return false;
        }

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

    protected:
        glm::vec2 m_LastMousePos{ -1,-1 };

        float m_MouseSensitivity{ .1f };
        float m_FlySpeed{ 3.f };
    };

    /**
     * @brief Preset camera controller class
     * Controls are WASD for flying around and QE for ascend/descend. Mouse movement rotates the camera in yaw/pitch axis
    */
    using FlyCameraController = FlyCameraControllerImpl<>;

    /************************************************************************/
    /* RMB Fly Camera                                                        */
    /************************************************************************/

    /**
     * @brief Preset camera controller class
     * Controls are WASD for flying around and QE for ascend/descend. Mouse movement rotates the camera in yaw/pitch axis
     * All actions are executed only if RMB is pressed. Controller also shows/hides mouse cursor
    */
    class RMBCaptureFlyCameraController : public FlyCameraControllerImpl<RMBCaptureFlyCameraController>
    {
    public:
        RMBCaptureFlyCameraController(const Ra::Camera& camera);

        void OnUpdate(const Timestep& ts) override;

        bool OnMouseMoved(MouseMovedEvent&) override;

        bool OnMouseButtonPressed(MouseButtonPressedEvent&) override;
        bool OnMouseButtonReleased(MouseButtonReleasedEvent&) override;

    private:
        using Base = FlyCameraControllerImpl<RMBCaptureFlyCameraController>;

        bool m_Captured{ false };

    };
}