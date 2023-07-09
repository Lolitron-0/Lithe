#pragma once
#include <RenderAbstraction.hpp>
#include "Lithe/Core/Timestep.hpp"
#include "Lithe/Events/Events.hpp"
#include "Lithe/Scene/Components.hpp"
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
    template<class Derived>
    class CameraController
    {
    public:
        CameraController(Entity& camera)
            :m_Camera(camera), m_Transform(&camera.GetComponent<TransformComponent>())
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

        Camera& GetCamera() { return m_Camera.GetComponent<CameraComponent>().Camera; }
        TransformComponent& GetTransform() { return *m_Transform; }

    protected:
        TransformComponent* m_Transform;
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
        FlyCameraControllerImpl(Entity& camera)
            :CameraController(camera)
        {}

        virtual void OnUpdate(const Timestep& ts) override
        {
            if (Keyboard::IsKeyPressed(Keyboard::Key::W))
                m_Transform->Translate(m_Transform->GetFront()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::A))
                m_Transform->Translate(-m_Transform->GetRight()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::S))
                m_Transform->Translate(-m_Transform->GetFront()*m_FlySpeed*(float)ts);
            if (Keyboard::IsKeyPressed(Keyboard::Key::D))
                m_Transform->Translate(m_Transform->GetRight()*m_FlySpeed*(float)ts);
        }

        virtual bool OnMouseMoved(MouseMovedEvent& event) override
        {
            auto xOffset = m_LastMousePos.x == -1 ? 0.f : m_LastMousePos.x - event.GetMouseX();
            auto yOffset = m_LastMousePos.y == -1 ? 0.f : m_LastMousePos.y - event.GetMouseY();

            m_Transform->RotateX(xOffset * m_MouseSensitivity);
            m_Transform->RotateY(yOffset * m_MouseSensitivity);

            /*if (m_Transform->GetRotation().y > 89.f)
                m_Transform->SetRotationY(89.f);

            if (m_Transform->GetRotation().y < -89.f)
                m_Transform->SetRotationY(-89.f);*/

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