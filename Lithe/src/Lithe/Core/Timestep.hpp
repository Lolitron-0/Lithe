#pragma once
#include <glm/glm.hpp>

namespace Lithe
{
    /// Class for inter-frame time measurement
    class Timestep
    {
    public:
        Timestep(double delta);

        /**
         * @brief Use this method to get proper FPS scale to multiply your movement data
         * @return FPS scale of this frame (non-linear) 
         * @note For code readability it is recommended to just multiply a value on a Timestep object using implicit conversion
        */
        double GetFpsScale() const { return m_FpsScale; }

        /// Returns number of seconds since the last frame
        double GetSeconds() const { return m_DeltaTime; }
        /// Returns number of milliseconds since the last frame
        double GetMilliseconds() const { return m_DeltaTime * 1'000.; }
        /// Returns number of microseconds since the last frame
        double GetMicroseconds() const { return m_DeltaTime * 1'000'000.; }

        /// Static time scale multiplier, default is 1.0
        static float TimeScale;

        operator double() const;

    private:
        constexpr static float s_LitheDefaultUnitsMult = 20.f;

        double m_FpsScale{0.0};
        double m_DeltaTime{0.0};
    };
}