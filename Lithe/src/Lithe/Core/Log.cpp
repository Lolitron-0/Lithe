#include "ltpch.h"
#include "Log.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace Lithe
{

    Log::LoggerPtr Log::m_CoreLogger;
    Log::LoggerPtr Log::m_ClientLogger;


    Log::CustomLoggerFunc Log::m_ClientLoggerCustomFunc = [](auto&&... params) -> decltype(auto) {};

    Log::CustomLoggerFunc Log::m_CoreLoggerCustomFunc = [](auto&&... params) -> decltype(auto) {};

    void Log::Init()
    {
        std::string pattern{ "%^[%T] %n: %v%$" };
        spdlog::set_pattern(pattern);

        auto m_CustomCoreSink = std::make_shared<custom_sink_mt>();
        m_CustomCoreSink->set_pattern(pattern);
        m_CustomCoreSink->IsClient = false;
        m_CoreLogger = spdlog::stdout_color_mt("LITHE");
        m_CoreLogger->sinks().push_back(m_CustomCoreSink);
        m_CoreLogger->set_level(spdlog::level::trace);

        auto m_CustomClientSink = std::make_shared<custom_sink_mt>();
        m_CustomClientSink->set_pattern(pattern);
        m_CustomClientSink->IsClient = true;
        m_ClientLogger = spdlog::stdout_color_mt("APP");
        m_ClientLogger->sinks().push_back(m_CustomClientSink);
        m_ClientLogger->set_level(spdlog::level::trace);

        LITHE_CORE_LOG_WARN("Logger initialised!");
    }

    void Log::SetClientLoggerCustomFunc(const CustomLoggerFunc& func)
    {
        m_ClientLoggerCustomFunc = func;
    }

    void Log::SetCoreLoggerCustomFunc(const CustomLoggerFunc& func)
    {
        m_CoreLoggerCustomFunc = func;
    }

}
