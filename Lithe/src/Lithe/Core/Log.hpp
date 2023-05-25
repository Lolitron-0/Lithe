/*****************************************************************//**
 * \file   Log.hpp
 * \brief  Logger header file
 * 
 * \author Lolitron
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "Base.hpp"
#include <spdlog/spdlog.h>

namespace Lithe
{
	/**
	* \brief Wrapper around spdlog interface.
	*
	* Static class holding two spdlog::logger instances: for client app logging and for core logging
	*/
	class LITHE_API Log
	{
	public:
		typedef std::shared_ptr<spdlog::logger> LoggerPtr;

		/**
		 * \brief Logger initialisation static function.
		 * 
		 * Logs a message if initialisation finished successfully
		 */
		static void Init();

		/// Core logger instance getter, not really ment to be used in client apps
		inline static LoggerPtr& GetCoreLogger();
		/// Client logger instance getter, not really ment to be used, use LITHE_* macros instead
		inline static LoggerPtr& GetClientLogger();

	private:
		static LoggerPtr coreLogger_;
		static LoggerPtr clientLogger_;
	};

}

/// Core fatal error logging
#define LITHE_CORE_FATAL(...)   ::Lithe::Log::GetCoreLogger()->fatal(__VA_ARGS__);
/// Core error logging
#define LITHE_CORE_ERROR(...)   ::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__);
/// Core warning logging
#define LITHE_CORE_WARN(...)    ::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__);
/// Core info logging
#define LITHE_CORE_INFO(...)    ::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__);
/// Core debug messages
#define LITHE_CORE_DEBUG(...)   ::Lithe::Log::GetCoreLogger()->debug(__VA_ARGS__);

/// Client fatal error logging
#define LITHE_FATAL(...)        ::Lithe::Log::GetClientLogger()->fatal(__VA_ARGS__);
/// Client error logging
#define LITHE_ERROR(...)        ::Lithe::Log::GetClientLogger()->error(__VA_ARGS__);
/// Client warning logging
#define LITHE_WARN(...)         ::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__);
/// Client info messages logging
#define LITHE_INFO(...)         ::Lithe::Log::GetClientLogger()->info(__VA_ARGS__);
/// Client debug messages logging
#define LITHE_DEBUG(...)        ::Lithe::Log::GetClientLogger()->debug(__VA_ARGS__);

