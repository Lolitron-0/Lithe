#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace Lithe
{

    Log::LoggerPtr Log::coreLogger_;
    Log::LoggerPtr Log::clientLogger_;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger_ = spdlog::stdout_color_mt("LITHE");
        coreLogger_->set_level(spdlog::level::trace);

        clientLogger_ = spdlog::stdout_color_mt("APP");
        clientLogger_->set_level(spdlog::level::trace);

        LITHE_CORE_WARN("Logger initialised!");
    }
}
