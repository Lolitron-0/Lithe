#include "ltpch.h"
#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace Lithe
{

    Log::LoggerPtr Log::m_CoreLogger;
    Log::LoggerPtr Log::m_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        m_CoreLogger = spdlog::stdout_color_mt("LITHE");
        m_CoreLogger->set_level(spdlog::level::trace);

        m_ClientLogger = spdlog::stdout_color_mt("APP");
        m_ClientLogger->set_level(spdlog::level::trace);

        LITHE_CORE_LOG_WARN("Logger initialised!");
    }
}
