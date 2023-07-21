#pragma once
#include <chrono>
#include <thread>
#include "Base.hpp"

namespace Lithe
{
    class Stopwatch
    {
    public:
        using ChronoTypes = TypeList<std::chrono::seconds, std::chrono::milliseconds, std::chrono::microseconds>;

        Stopwatch()
        {
            Start();
        }

        void Start()
        {
            m_Start = std::chrono::steady_clock::now();
        }

        template<class T = std::chrono::microseconds>
        typename std::enable_if<Contains<T, ChronoTypes>::value,std::uint64_t>
            ::type Elapsed() const
        {
            auto endTime{ std::chrono::steady_clock::now() };
            auto highResStart{ std::chrono::duration<double, std::milli>{ m_Start.time_since_epoch() } };
            auto elapsed{ std::chrono::time_point_cast<T>(endTime).time_since_epoch() -
    std::chrono::time_point_cast<T>(m_Start).time_since_epoch() };
            return elapsed.count();
        }

        template<class T = std::chrono::microseconds>
        typename std::enable_if<Contains<T, ChronoTypes>::value, std::uint64_t>
            ::type Reset()
        {
            auto el = Elapsed();
            Start();
            return el;
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> m_Start;
    };
}