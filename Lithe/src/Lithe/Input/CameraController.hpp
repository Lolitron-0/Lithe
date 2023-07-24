#pragma once
#include <RenderAbstraction.hpp>
#include "Lithe/Core/Timestep.hpp"
#include "Lithe/Events/Events.hpp"
#include "Lithe/Scene/Components/Components.hpp"
#include "Lithe/Scene/Entity.hpp"
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
    template<class Derived = NullType>
    class CameraController
    {
    public:
        CameraController(const Entity& camera)
            :m_Camera(camera)
        {
        }
        virtual ~CameraController() = default;

        void OnEvent(Event& event)
        {
            EventDispatcher dispatcher{ event };
            dispatcher.Dispatch<MouseMovedEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnMouseMoved, Derived));
            dispatcher.Dispatch<MouseButtonPressedEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnMouseButtonPressed, Derived));
            dispatcher.Dispatch<MouseButtonReleasedEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnMouseButtonReleased, Derived));
            dispatcher.Dispatch<KeyPressedEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnKeyPressed, Derived));
            dispatcher.Dispatch<KeyReleasedEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnKeyReleased, Derived));
            dispatcher.Dispatch<MouseScrolledEvent>(LT_BIND_EVENT_FN_CASTED_THIS(OnMouseScrolled, Derived));
        }
        virtual void OnUpdate(const Timestep& ts) {}
        virtual bool OnKeyPressed(KeyPressedEvent& event) { return false; };
        virtual bool OnKeyReleased(KeyReleasedEvent& event) { return false; };
        virtual bool OnMouseMoved(MouseMovedEvent&) { return false; };
        virtual bool OnMouseButtonPressed(MouseButtonPressedEvent&) { return false; };
        virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent&) { return false; };
        virtual bool OnMouseScrolled(MouseScrolledEvent&) { return false; };

        Ref<Camera> GetCamera() { return m_Camera.GetComponent<CameraComponent>().Camera; }
        TransformComponent& GetTransform() { return m_Camera.GetComponent<TransformComponent>(); }

    protected:
        Entity m_Camera;
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
        FlyCameraControllerImpl(const Entity& camera)
            :CameraController(camera)
        {}

        void OnUpdate(const Timestep& ts) override
        {
            if (!Application::GetInstance().GetWindow().IsCursorHidden())
                Application::GetInstance().GetWindow().HideCursor();
            if (Keyboard::IsKeyPressed(Keyboard::Key::W))
                GetTransform().Translate(GetTransform().GetFront()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::A))
                GetTransform().Translate(-GetTransform().GetRight()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::S))
                GetTransform().Translate(-GetTransform().GetFront()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::D))
                GetTransform().Translate(GetTransform().GetRight()*m_FlySpeed*(float)ts);
        }

        bool OnKeyPressed(KeyPressedEvent& event) 
        { 
            if (event.GetKeyCode() == Keyboard::Key::LeftShift && !event.IsRepeated())
                m_FlySpeed *= 2;

            if (event.GetKeyCode() == Keyboard::Key::Equal)
            {
                m_FlySpeed *= 1.25f;
                LITHE_CORE_LOG_TRACE("Fly speed: {0}", (int)m_FlySpeed);
            }

            if (event.GetKeyCode() == Keyboard::Key::Minus)
            {
                m_FlySpeed /= 1.25f;
                LITHE_CORE_LOG_TRACE("Fly speed: {0}", (int)m_FlySpeed);
            }

            return false; 
        };

        bool OnKeyReleased(KeyReleasedEvent& event) 
        {
            if (event.GetKeyCode() == Keyboard::Key::LeftShift)
                m_FlySpeed /= 2;
            return false; 
        };

        bool OnMouseMoved(MouseMovedEvent& event) override
        {
            auto xOffset = m_LastMousePos.x == -1 ? 0.f : m_LastMousePos.x - event.GetMouseX();
            auto yOffset = m_LastMousePos.y == -1 ? 0.f : m_LastMousePos.y - event.GetMouseY();

            GetTransform().RotateY(-event.GetOffsetX() * m_MouseSensitivity);
            GetTransform().RotateX(event.GetOffsetY() * m_MouseSensitivity);

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
        float m_FlySpeed{ 25.f };
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
        RMBCaptureFlyCameraController(Entity& camera);

        void OnUpdate(const Timestep& ts) override;

        bool OnMouseMoved(MouseMovedEvent&) override;

        bool OnMouseButtonPressed(MouseButtonPressedEvent&) override;
        bool OnMouseButtonReleased(MouseButtonReleasedEvent&) override;

    private:
        using Base = FlyCameraControllerImpl<RMBCaptureFlyCameraController>;

        bool m_Captured{ false };

    };
}