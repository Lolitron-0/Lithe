#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Lithe
{
    using Vec4 = glm::vec4;
    using Vec3 = glm::vec3;
    using Vec2 = glm::vec2;
    using Mat4  = glm::mat4;
    using Mat3  = glm::mat3;
    using Mat3  = glm::mat3;
    using Quat = glm::quat;

    template<class T>
    inline T VecToRadians(const T& v)
    {
        T res = v;
        for (typename T::length_type i{ 0 }; i < v.length(); i++)
            res[i] = glm::radians(res[i]);
        return res;
    }

    template<class T>
    inline T VecToDegrees(const T& v)
    {
        T res = v;
        for (typename T::length_type i{ 0 }; i < v.length(); i++)
            res[i] = glm::degrees(res[i]);
        return res;
    }

    inline Mat4 MakeRotationFromEuler(const Vec3& angles)
    {
        return glm::yawPitchRoll(angles.x, angles.y, angles.z);
    }

    inline Mat4 MakePerspective(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 100.f)
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

    template<class T>
    inline T Normalized(const T& obj)
    {
        return glm::normalize(obj);
    }

    inline Vec3 MakeEulerAngles(const Quat& quaternion)
    {
        return glm::eulerAngles(quaternion);
    }

    template<class T>
    inline T Cross(const T& o1, const T& o2)
    {
        return glm::cross(o1, o2);
    }
}