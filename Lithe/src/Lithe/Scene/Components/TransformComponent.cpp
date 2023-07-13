#include "ltpch.h"
#include "TransformComponent.hpp"
#include "Lithe/Core/Application.hpp"

namespace Lithe
{
    const Mat4& TransformComponent::GetMatrix() const
    {
        if (m_ShouldUpdateMatrix)
        {
            Mat4 translation = glm::translate(Mat4{ 1.f }, m_Position);
            Mat4 rotation = MakeRotationFromEuler(VecToRadians(m_Rotation));
            Mat4 scale = glm::scale(Mat4{ 1.f }, m_Scale);
            m_Transform = translation * rotation * scale;
            m_ShouldUpdateMatrix = false;
        }
        return m_Transform;
    }

    Lithe::Vec3 TransformComponent::GetPosition() const
    {
        return m_Position;
    }

    Lithe::Vec3 TransformComponent::GetRotation() const
    {
        return m_Rotation;
    }

    Lithe::Vec3 TransformComponent::GetScale() const
    {
        return m_Scale;
    }

    Lithe::Vec3 TransformComponent::GetFront() const
    {
        return -Normalized(MakeRotationFromEuler(VecToRadians(m_Rotation)) * Vec4{ 0, 0, 1 , 1});
    }

    Lithe::Vec3 TransformComponent::GetRight() const
    {
        return Normalized(Cross(GetFront(), { 0,1,0 }));
    }

    Lithe::TransformComponent& TransformComponent::SetPosition(const Vec3& pos)
    {
        m_Position = pos;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::SetRotation(const Vec3& rotation)
    {
        m_Rotation = {0,0,0};
        return this->Rotate(rotation);
    }

    TransformComponent& TransformComponent::SetRotation(const Quat& quaternion)
    {
        return this->SetRotation(VecToDegrees(MakeEulerAngles(quaternion)));
    }

    Lithe::TransformComponent& TransformComponent::SetRotationX(float value)
    {
        m_Rotation.x = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::SetRotationY(float value)
    {
        m_Rotation.y = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::SetRotationZ(float value)
    {
        m_Rotation.z = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::SetScale(const Vec3& scale)
    {
        m_Scale = scale;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::SetScale(float scaleFactor)
    {
        m_Scale = Vec3{ scaleFactor };
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::Translate(const Vec3& dist)
    {
        m_Position += dist;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::TranslateX(float value)
    {
        return this->Translate({ value, 0.f, 0.f });
    }

    Lithe::TransformComponent& TransformComponent::TranslateY(float value)
    {
        return this->Translate({ 0.f, value, 0.f });
    }

    Lithe::TransformComponent& TransformComponent::TranslateZ(float value)
    {
        return this->Translate({ 0.f, 0.f, value });
    }

    Lithe::TransformComponent& TransformComponent::Rotate(const Vec3& angles)
    {
        m_Rotation += angles;
        m_Rotation.x = std::fmod(m_Rotation.x + 360.f, 360.f);
        m_Rotation.y = std::fmod(m_Rotation.y + 360.f, 360.f);
        m_Rotation.z = std::fmod(m_Rotation.z + 360.f, 360.f);
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::RotateX(float value)
    {
        return this->Rotate({ value, 0.f, 0.f });
    }

    Lithe::TransformComponent& TransformComponent::RotateY(float value)
    {
        return this->Rotate({ 0.f, value, 0.f });
    }

    Lithe::TransformComponent& TransformComponent::RotateZ(float value)
    {
        return this->Rotate({ 0.f, 0.f, value });
    }

    Lithe::TransformComponent& TransformComponent::LookAt(const Vec3& target)
    {
        auto q = glm::quatLookAt(Normalized(target - m_Position), {0.0001f,1,0});

        return this->SetRotation(q);
    }

    Lithe::TransformComponent& TransformComponent::Scale(const Vec3& factor)
    {
        m_Scale += factor;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    Lithe::TransformComponent& TransformComponent::Scale(float factor)
    {
        return this->Scale(Vec3{ factor });
    }

    Lithe::TransformComponent& TransformComponent::ScaleX(float factor)
    {
        return this->Scale({ factor, 1.f, 1.f });
    }

    Lithe::TransformComponent& TransformComponent::ScaleY(float factor)
    {
        return this->Scale({ 1.f, factor, 1.f });
    }

    Lithe::TransformComponent& TransformComponent::ScaleZ(float factor)
    {
        return this->Scale({ 1.f, 1.f, factor });
    }

    void TransformComponent::OnImGuiPropertiesDraw()
    {
        if (ImGui::DragFloat3("Position", glm::value_ptr(m_Position), .01f))
            m_ShouldUpdateMatrix = true; 

        if (ImGui::DragFloat3("Rotation", glm::value_ptr(m_Rotation), .5f))
            m_ShouldUpdateMatrix = true;

        if (ImGui::DragFloat3("Scale", glm::value_ptr(m_Scale), .01f))
            m_ShouldUpdateMatrix = true;

        if(ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            Application::GetInstance().GetWindow().SetCursorWrap(true);
    }

}

