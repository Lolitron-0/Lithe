#pragma once
#include "Lithe/Core/Math.hpp"
#include "ComponentBase.hpp"

namespace Lithe
{
    class TransformComponent : public ComponentBase
    {
        MAKE_COMPONENT(TransformComponent)
    public:

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Mat4& transform)
            :m_Transform(transform)
        {}
        TransformComponent(const Vec3& position, const Vec3& rotation, const Vec3 scale = { 1,1,1 })
            :m_Position(position), m_Rotation(rotation), m_Scale(scale)
        {}

        const Mat4& GetMatrix() const;
        const Mat4& GetNormalMatrix() const;

        operator const Mat4& () const { return GetMatrix(); }

        Vec3 GetPosition() const; 
        Vec3 GetRotation() const;
        Vec3 GetScale() const;
        Vec3 GetFront() const;
        Vec3 GetRight() const;

        TransformComponent& SetPosition(const Vec3& pos);
        TransformComponent& SetRotation(const Vec3& rotation);
        TransformComponent& SetRotation(const Quat& quaternion);
        TransformComponent& SetRotationX(float value);
        TransformComponent& SetRotationY(float value);
        TransformComponent& SetRotationZ(float value);
        TransformComponent& SetScale(const Vec3& scale);
        TransformComponent& SetScale(float scaleFactor);

        TransformComponent& Translate(const Vec3& dist);
        TransformComponent& TranslateX(float value);
        TransformComponent& TranslateY(float value);
        TransformComponent& TranslateZ(float value);

        TransformComponent& Rotate(const Vec3& angles);
        TransformComponent& RotateX(float value);
        TransformComponent& RotateY(float value);
        TransformComponent& RotateZ(float value);
        /// @todo NOT WORKING
        TransformComponent& LookAt(const Vec3& target);

        TransformComponent& Scale(const Vec3& factor);
        TransformComponent& Scale(float factor);
        TransformComponent& ScaleX(float factor);
        TransformComponent& ScaleY(float factor);
        TransformComponent& ScaleZ(float factor);
    

        void OnImGuiPropertiesDraw() override;

    private:
        Vec3 m_Position{ 0,0,0 };
        Vec3 m_Rotation{ 0,0,0 };
        Vec3 m_Scale{ 1,1,1 };
        mutable Mat4 m_Transform{ 1.f };
        mutable Mat4 m_NormalMatrix{ 1.f };
        mutable bool m_ShouldUpdateMatrix{ true };
    };

}