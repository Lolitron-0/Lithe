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
        typedef std::shared_ptr<spdlog::logger> LoggerPtr;

        /**
         * @brief Logger initialisation static function.
         *
         * Logs a message if initialisation finished successfully
         */
        static void Init();

        /// Core logger instance getter, not really ment to be used in client apps
        inline static LoggerPtr& GetCoreLogger() { return m_CoreLogger; }
        /// Client logger instance getter, not really ment to be used, use LITHE_* macros instead
        inline static LoggerPtr& GetClientLogger() { return m_ClientLogger; }

    private:
        static LoggerPtr m_CoreLogger;
        static LoggerPtr m_ClientLogger;
    };

}

#pragma warning( push )
#pragma warning( disable : 4251 )

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
#define LITHE_CORE_FATAL(...)   ::Lithe::Log::GetCoreLogger()->fatal(__VA_ARGS__);
/// Core error logging
#define LITHE_CORE_ERROR(...)   ::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__);
/// Core warning logging
#define LITHE_CORE_WARN(...)    ::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__);
/// Core info logging
#define LITHE_CORE_INFO(...)    ::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__);
/// Core trace messages logging
#define LITHE_CORE_TRACE(...)   ::Lithe::Log::GetCoreLogger()->trace(__VA_ARGS__);
/// Core debug messages logging
#define LITHE_CORE_DEBUG(...)   ::Lithe::Log::GetCoreLogger()->debug(__VA_ARGS__);

/// Client fatal error logging
#define LITHE_FATAL(...)        ::Lithe::Log::GetClientLogger()->fatal(__VA_ARGS__);
/// Client error logging
#define LITHE_ERROR(...)        ::Lithe::Log::GetClientLogger()->error(__VA_ARGS__);
/// Client warning logging
#define LITHE_WARN(...)         ::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__);
/// Client info messages logging
#define LITHE_INFO(...)         ::Lithe::Log::GetClientLogger()->info(__VA_ARGS__);
/// Client trace messages logging
#define LITHE_TRACE(...)        ::Lithe::Log::GetClientLogger()->trace(__VA_ARGS__);
/// Client debug messages logging
#define LITHE_DEBUG(...)        ::Lithe::Log::GetClientLogger()->debug(__VA_ARGS__);

#pragma warning( pop )
