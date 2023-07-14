#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Lithe
{
    using Vec4 = glm::vec4;
    using Vec3 = glm::vec3;
    using Vec2 = glm::vec2;
    using Mat4 = glm::mat4;
    using Mat3 = glm::mat3;
    using Mat3 = glm::mat3;
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
        return glm::yawPitchRoll(angles.y, angles.x, angles.z);
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

    inline Mat4 Inverse(const Mat4& m)
    {
        return glm::inverse(m);
    }

    inline bool DecomposeMatrix(const Mat4& transform, Vec3& translation, Vec3& rotation, Vec3& scale)
    {
        // From glm/gtx/matrix_decompose.hpp (.inl)

        using namespace glm;
        using T = float;

        mat4 LocalMatrix(transform);

        // Normalize the matrix.
        if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
            return false;

        // First, isolate perspective.  This is the messiest.
        if (
            epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
            epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
            epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
        {
            // Clear the perspective partition
            LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
            LocalMatrix[3][3] = static_cast<T>(1);
        }

        // Next take care of translation (easy).
        translation = vec3(LocalMatrix[3]);
        LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

        vec3 Row[3];

        // Now get scale and shear.
        for (length_t i = 0; i < 3; ++i)
            for (length_t j = 0; j < 3; ++j)
                Row[i][j] = LocalMatrix[i][j];

        // Compute X scale factor and normalize first row.
        scale.x = length(Row[0]);
        Row[0] = detail::scale(Row[0], static_cast<T>(1));
        scale.y = length(Row[1]);
        Row[1] = detail::scale(Row[1], static_cast<T>(1));
        scale.z = length(Row[2]);
        Row[2] = detail::scale(Row[2], static_cast<T>(1));

        // At this point, the matrix (in rows[]) is orthonormal.
        // Check for a coordinate system flip.  If the determinant
        // is -1, then negate the matrix and the scaling factors.
#if 0
        Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
        if (dot(Row[0], Pdum3) < 0)
        {
            for (length_t i = 0; i < 3; i++)
            {
                scale[i] *= static_cast<T>(-1);
                Row[i] *= static_cast<T>(-1);
            }
        }
#endif

        rotation.y = asin(-Row[0][2]);
        if (cos(rotation.y) != 0) {
            rotation.x = atan2(Row[1][2], Row[2][2]);
            rotation.z = atan2(Row[0][1], Row[0][0]);
        }
        else {
            rotation.x = atan2(-Row[2][0], Row[1][1]);
            rotation.z = 0;
        }
        rotation = VecToDegrees(rotation);

        return true;
    }
}