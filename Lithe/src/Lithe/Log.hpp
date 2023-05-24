#pragma once
#include "Core.hpp"
#include <spdlog/spdlog.h>
#include <memory>

namespace Lithe
{
	class LITHE_API Log
	{
	public:
		typedef std::shared_ptr<spdlog::logger> LoggerPtr;

		static void Init();

		inline static LoggerPtr& GetCoreLogger();
		inline static LoggerPtr& GetClientLogger();

	private:
		static LoggerPtr coreLogger_;
		static LoggerPtr clientLogger_;
	};

}

#ifdef LT_BUILD_DLL
	#define LITHE_CORE_FATAL(...)   ::Lithe::Log::GetCoreLogger()->fatal(__VA_ARGS__);
	#define LITHE_CORE_ERROR(...)   ::Lithe::Log::GetCoreLogger()->error(__VA_ARGS__);
	#define LITHE_CORE_WARN(...)    ::Lithe::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define LITHE_CORE_INFO(...)    ::Lithe::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define LITHE_CORE_DEBUG(...)   ::Lithe::Log::GetCoreLogger()->debug(__VA_ARGS__);
#else
	#define LITHE_CORE_FATAL(...)
	#define LITHE_CORE_ERROR(...)
	#define LITHE_CORE_WARN(...) 
	#define LITHE_CORE_INFO(...) 
	#define LITHE_CORE_DEBUG(...)
#endif

#define LITHE_FATAL(...)        ::Lithe::Log::GetClientLogger()->fatal(__VA_ARGS__);
#define LITHE_ERROR(...)        ::Lithe::Log::GetClientLogger()->error(__VA_ARGS__);
#define LITHE_WARN(...)         ::Lithe::Log::GetClientLogger()->warn(__VA_ARGS__);
#define LITHE_INFO(...)         ::Lithe::Log::GetClientLogger()->info(__VA_ARGS__);
#define LITHE_DEBUG(...)        ::Lithe::Log::GetClientLogger()->debug(__VA_ARGS__);

