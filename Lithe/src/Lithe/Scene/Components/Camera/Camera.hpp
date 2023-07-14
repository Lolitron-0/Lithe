#pragma once
#include "Lithe/Core/Math.hpp"
#include <any>

namespace Lithe
{
    class Camera
    {
    public:
        Camera();
        Camera(float aspectRatio);
        Camera(const Mat4& projection);
        Camera(const Camera&) = default;
        virtual ~Camera() = default;

        Mat4& GetProjection();
        const Mat4& GetProjection() const;

        void SetAspectRatio(float ratio);

        template<class T>
        T GetCameraProperties() { return std::any_cast<T>(this->GetCameraPropertiesImpl_()); }
        template<class T>
        void SetCameraProperties(const T& properties) 
        { 
            this->SetCameraPropertiesImpl_(properties);
            m_ShouldRecalculateProjection = true; 
        }

    protected:
        virtual void RecalculateProjection_() const = 0;
        virtual std::any GetCameraPropertiesImpl_() const { return std::any{}; };
        virtual void SetCameraPropertiesImpl_(const std::any& val) = 0;
         
        mutable Mat4 m_Projection;
        mutable float m_ShouldRecalculateProjection{ true };
        float m_AspectRatio{ 16.f / 9.f };
    };
}