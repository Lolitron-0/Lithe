/*****************************************************************//**
 * @file   Log.hpp
 * @brief  Logger header file
 *
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include "Base.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Important: should be included after main header
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <spdlog/sinks/base_sink.h>

namespace Lithe
{
    /**
    * @brief Wrapper around spdlog interface.
    *
    * Static class holding two spdlog::logger instances: for client app logging and for core logging
    */
    class LITHE_API Log
    {   
    public:
        /// Log message severity enum
        enum class Severity : std::uint8_t
        {
            Debug,
            Trace,
            Info,
            Warning,
            Error,
            Fatal,
        };

        using LoggerPtr = std::shared_ptr<spdlog::logger>;
        using CustomLoggerFunc = std::function<void(const std::string& message, const Log::Severity& severity)>;

        /**
         * @brief Logger initialization static function.
         *
         * Logs a message if initialization finished successfully
         */
        static void Init();

        /// Core logger instance getter, not really meant to be used in client apps
        inline static LoggerPtr& GetCoreLogger() { return m_CoreLogger; }
        /// Client logger instance getter, not really ment to be used, use LITHE_LOG_* macros instead
        inline static LoggerPtr& GetClientLogger() { return m_ClientLogger; }

        /// Sets function to be executed on every LITHE_LOG_* call
        static void SetClientLoggerCustomFunc(const CustomLoggerFunc& func);
        /// Sets function to be executed on every LITHE_CORE_LOG_* call
        static void SetCoreLoggerCustomFunc(const CustomLoggerFunc& func);

        inline static CustomLoggerFunc& GetClientLoggerCustomFunc() { return m_ClientLoggerCustomFunc; }
        inline static CustomLoggerFunc& GetCoreLoggerCustomFunc() { return m_CoreLoggerCustomFunc; }

    private:
        static LoggerPtr m_CoreLogger;
        static LoggerPtr m_ClientLogger;
        static CustomLoggerFunc m_ClientLoggerCustomFunc;
        static CustomLoggerFunc m_CoreLoggerCustomFunc;
    };

}


template<class Mutex>
class custom_sink : public spdlog::sinks::base_sink<Mutex>
{
public:
    bool IsClient{ false };

protected:
    void sink_it_(const spdlog::details::log_msg& msg) override
    {
        auto& fn = IsClient ? Lithe::Log::GetClientLoggerCustomFunc() : Lithe::Log::GetCoreLoggerCustomFunc();
        spdlog::memory_buf_t formatted;
        spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);
        auto formattedStr = fmt::to_string(formatted);
        switch (msg.level)
        {
        case spdlog::level::trace:
            fn(formattedStr, Lithe::Log::Severity::Trace);
            break;
        case spdlog::level::debug:
            fn(formattedStr, Lithe::Log::Severity::Debug);
            break;
        case spdlog::level::info:
            fn(formattedStr, Lithe::Log::Severity::Info);
            break;
        case spdlog::level::warn:
            fn(formattedStr, Lithe::Log::Severity::Warning);
            break;
        case spdlog::level::err:
            fn(formattedStr, Lithe::Log::Severity::Error);
            break;
        case spdlog::level::critical:
            fn(formattedStr, Lithe::Log::Severity::Fatal);
            break;
        default:
            break;
        }
    }


    void flush_() override
    {
        
    }
};

#include "spdlog/details/null_mutex.h"
#include <mutex>
using custom_sink_mt = custom_sink<std::mutex>;
using custom_sink_st = custom_sink<spdlog::details::null_mutex>;

/// glm::vec logging
template<class OStream, glm::length_t L, class T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& v)
{
    return os << glm::to_string(v);
}

/// glm::mat logging
template<class OStream, glm::length_t C, glm::length_t R, class T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& m)
{
    return os << glm::to_string(m);
}

/// glm::qua logging
template<class OStream, class T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::qua<T, Q>& q)
{
    return os << glm::to_string(q);
}



/// Core fatal error logging
#define LITHE_CORE_LOG_FATAL(...)   ::Lithe::Log::GetCoreLogger()->fatal(__VA_ARGS__);
/// Core error logging
#define LITHE_CORE_LOG_ERROR(...)   ::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__);
/// Core warning logging
#define LITHE_CORE_LOG_WARN(...)    ::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__);
/// Core info logging
#define LITHE_CORE_LOG_INFO(...)    ::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__);
/// Core trace messages logging
#define LITHE_CORE_LOG_TRACE(...)   ::Lithe::Log::GetCoreLogger()->trace(__VA_ARGS__);
/// Core debug messages logging
#define LITHE_CORE_LOG_DEBUG(...)   ::Lithe::Log::GetCoreLogger()->debug(__VA_ARGS__);

/// Client fatal error logging
#define LITHE_LOG_FATAL(...)        ::Lithe::Log::GetClientLogger()->fatal(__VA_ARGS__);
/// Client error logging
#define LITHE_LOG_ERROR(...)        ::Lithe::Log::GetClientLogger()->error(__VA_ARGS__);
/// Client warning logging
#define LITHE_LOG_WARN(...)         ::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__);
/// Client info messages logging
#define LITHE_LOG_INFO(...)         ::Lithe::Log::GetClientLogger()->info(__VA_ARGS__);
/// Client trace messages logging
#define LITHE_LOG_TRACE(...)        ::Lithe::Log::GetClientLogger()->trace(__VA_ARGS__);
/// Client debug messages logging
#define LITHE_LOG_DEBUG(...)        ::Lithe::Log::GetClientLogger()->debug(__VA_ARGS__);
