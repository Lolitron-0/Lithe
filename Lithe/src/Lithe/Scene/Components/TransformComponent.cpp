#include "ltpch.h"
#include "TransformComponent.hpp"
#include "Lithe/Core/Application.hpp"
#include <imgui_internal.h>

namespace Lithe
{
    bool DrawVec3Control(const std::string& label, Vec3& values, float speed = 0.01f, float resertValue = 0.0f, float columnWidth = 100.f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[1];

        ImGui::PushID(label.c_str());

        bool ret = false;

        ImGui::Columns(2);

        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.f);

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.f;
        ImVec2 buttonSize{ lineHeight + 3.f, lineHeight };

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.25f, 0.2f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.7f, 0.05f, 0.07f, 1 });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
        {
            values.x = resertValue;
            ret = true;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::DragFloat("##X", &values.x, speed))
            ret = true;
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.75f, 0.17f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.9f, 0.2f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.7f, 0.07f, 1 });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
        {
            values.y = resertValue;
            ret = true;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::DragFloat("##Y", &values.y, speed))
            ret = true;
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.15f, 0.25f, 0.9f, 1 });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.05f, 0.05f, 0.7f, 1 });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
        {
            values.z = resertValue;
            ret = true;
        }
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        if (ImGui::DragFloat("##Z", &values.z, speed))
            ret = true;
        ImGui::PopItemWidth();

        ImGui::PopStyleVar(2);

        ImGui::Columns(1);

        ImGui::PopID();

        return ret;
    }


    const Mat4& TransformComponent::GetMatrix() const
    {
        if (m_ShouldUpdateMatrix)
        {
            Mat4 translation = glm::translate(Mat4{ 1.f }, m_Position);
            Mat4 rotation = glm::toMat4(Quat(VecToRadians(m_Rotation)));
            Mat4 scale = glm::scale(Mat4{ 1.f }, m_Scale);
            m_Transform = translation * rotation * scale;
            m_NormalMatrix = glm::transpose(glm::inverse(m_Transform));

            m_ShouldUpdateMatrix = false;
        }
        return m_Transform;
    }

    const Mat4& TransformComponent::GetNormalMatrix() const
    {
        (void)GetMatrix();
        return m_NormalMatrix;
    }

    Vec3 TransformComponent::GetPosition() const
    {
        return m_Position;
    }

    Vec3 TransformComponent::GetRotation() const
    {
        return m_Rotation;
    }

    Vec3 TransformComponent::GetScale() const
    {
        return m_Scale;
    }

    Vec3 TransformComponent::GetFront() const
    {
        return glm::rotate(Quat(VecToRadians(Vec3{ m_Rotation.x, m_Rotation.y, 0.f })), { 0, 0, -1.f });
    }

    Vec3 TransformComponent::GetRight() const
    {
        return glm::rotate(Quat(VecToRadians(Vec3{ m_Rotation.x, m_Rotation.y, 0.f })), { 1.f, 0, 0 });
    }

    Lithe::Vec3 TransformComponent::GetUp() const
    {
        return glm::rotate(Quat(VecToRadians(Vec3{ m_Rotation.x, m_Rotation.y, 0.f })), { 0, 1.f, 0 });
    }

    TransformComponent& TransformComponent::SetPosition(const Vec3& pos)
    {
        m_Position = pos;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::SetRotation(const Vec3& rotation)
    {
        m_Rotation = { 0,0,0 };
        return this->Rotate(rotation);
    }

    TransformComponent& TransformComponent::SetRotation(const Quat& quaternion)
    {
        return this->SetRotation(VecToDegrees(MakeEulerAngles(quaternion)));
    }

    TransformComponent& TransformComponent::SetRotationX(float value)
    {
        m_Rotation.x = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::SetRotationY(float value)
    {
        m_Rotation.y = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::SetRotationZ(float value)
    {
        m_Rotation.z = value;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::SetScale(const Vec3& scale)
    {
        m_Scale = scale;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::SetScale(float scaleFactor)
    {
        m_Scale = Vec3{ scaleFactor };
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::Translate(const Vec3& dist)
    {
        m_Position += dist;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::TranslateX(float value)
    {
        return this->Translate({ value, 0.f, 0.f });
    }

    TransformComponent& TransformComponent::TranslateY(float value)
    {
        return this->Translate({ 0.f, value, 0.f });
    }

    TransformComponent& TransformComponent::TranslateZ(float value)
    {
        return this->Translate({ 0.f, 0.f, value });
    }

    TransformComponent& TransformComponent::Rotate(const Vec3& angles)
    {
        m_Rotation += angles;
        m_Rotation.x = std::fmod(m_Rotation.x + 360.f, 360.f);
        m_Rotation.y = std::fmod(m_Rotation.y + 360.f, 360.f);
        m_Rotation.z = std::fmod(m_Rotation.z + 360.f, 360.f);
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::RotateX(float value)
    {
        return this->Rotate({ value, 0.f, 0.f });
    }

    TransformComponent& TransformComponent::RotateY(float value)
    {
        return this->Rotate({ 0.f, value, 0.f });
    }

    TransformComponent& TransformComponent::RotateZ(float value)
    {
        return this->Rotate({ 0.f, 0.f, value });
    }

    TransformComponent& TransformComponent::LookAt(const Vec3& target)
    {
        auto q = glm::quatLookAt(Normalized(target - m_Position), { 0.0001f,1,0 });

        return this->SetRotation(q);
    }

    TransformComponent& TransformComponent::Scale(const Vec3& factor)
    {
        m_Scale += factor;
        m_ShouldUpdateMatrix = true;
        return *this;
    }

    TransformComponent& TransformComponent::Scale(float factor)
    {
        return this->Scale(Vec3{ factor });
    }

    TransformComponent& TransformComponent::ScaleX(float factor)
    {
        return this->Scale({ factor, 1.f, 1.f });
    }

    TransformComponent& TransformComponent::ScaleY(float factor)
    {
        return this->Scale({ 1.f, factor, 1.f });
    }

    TransformComponent& TransformComponent::ScaleZ(float factor)
    {
        return this->Scale({ 1.f, 1.f, factor });
    }

    void TransformComponent::OnImGuiPropertiesDraw()
    {
        if (DrawVec3Control("Position", m_Position))
            m_ShouldUpdateMatrix = true;
        if (DrawVec3Control("Rotation", m_Rotation, 0.5f))
            m_ShouldUpdateMatrix = true;
        if (DrawVec3Control("Scale", m_Scale, 0.01f, 1.f))
            m_ShouldUpdateMatrix = true;
    }

}

