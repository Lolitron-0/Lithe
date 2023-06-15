/*****************************************************************//**
 * @file   Base.hpp
 * @brief  Main macros defines
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_DLL
		#define LITHE_API __declspec(dllexport)
	#else
		#define LITHE_API __declspec(dllimport)
	#endif
#else
	#error Lithe only supports Windows (for now)
#endif

#ifdef LT_DEBUG
	#ifdef LT_PLATFORM_WINDOWS
		#define LT_DEBUGBREAK() __debugbreak()
	#endif

	#define LT_ASSERTIONS
#endif

/// Needed to stop substitution and pass only a name (if x is a macro name)
#define LT_EXPAND(x) x

#define BIT(x) (1<<x)

/// Since all event functions are member (and need 'this' pointer) we need to wrap them in lambdas hooking 'this'
#define LT_BIND_EVENT_FN(fn) [this](auto&&... params) -> decltype(auto) {return this->fn(std::forward<decltype(params)>(params)...);}
