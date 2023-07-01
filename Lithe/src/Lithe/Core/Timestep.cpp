#include "ltpch.h"
#include "Timestep.hpp"

namespace Lithe
{

    Timestep::Timestep(double delta) 
        : m_DeltaTime(delta)
    {
        m_FpsScale = (1.0 - glm::pow(0.95, m_DeltaTime)) * s_LitheDefaultUnitsMult * TimeScale;
    }

    float Timestep::TimeScale = 1.f;

}

