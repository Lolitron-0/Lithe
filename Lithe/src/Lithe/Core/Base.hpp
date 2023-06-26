/*****************************************************************//**
 * @file   Base.hpp
 * @brief  Core defines
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include <memory>

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_STATIC
		#define LITHE_API //__declspec(dllexport)
	#else
		#define LITHE_API //__declspec(dllimport)
	#endif
#else
	#error Lithe only supports Windows!
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


namespace Lithe
{
	template<class T>
	using Scope = std::unique_ptr<T>;


	template<class T>
	using Ref = std::shared_ptr<T>;
}
