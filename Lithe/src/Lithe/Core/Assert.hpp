/*****************************************************************//**
 * \file   Assert.hpp
 * \brief  Definitions of assertion macros
 * 
 * \author Lolitron
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "Base.hpp"
#include "Log.hpp"
#include <filesystem>

#ifdef LT_ASSERTIONS
	#define LT_FILENAME std::filesystem::path(__FILE__).filename().string()

	#define LT_INTERNAL_ASSERT_IMPL(type, cond, msg, ...) {if (!(cond)) {LITHE##type##ERROR(msg, __VA_ARGS__); LT_DEBUGBREAK();}}
	#define LT_INTERNAL_ASSERT_IMPL_WITH_MSG(type, cond, ...) LT_INTERNAL_ASSERT_IMPL(type, cond, "{0}:{1} Assertion failed: {2}", LT_FILENAME, __LINE__, __VA_ARGS__)
	#define LT_INTERNAL_ASSERT_IMPL_NO_MSG(type, cond) LT_INTERNAL_ASSERT_IMPL(type, cond, "{0}:{1} Assertion failed!", LT_FILENAME, __LINE__)
		
	#define LT_INTERNAL_ASSERT_GET_MACRO_NAME(_1, _2, NAME, ...) NAME
	#define LT_INTERNAL_ASSERT_GET_MACRO(...) LT_EXPAND( LT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LT_INTERNAL_ASSERT_IMPL_WITH_MSG, LT_INTERNAL_ASSERT_IMPL_NO_MSG) )
	#define LITHE_CORE_ASSERT(...) LT_EXPAND( LT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
	#define LITHE_ASSERT(...) LT_EXPAND( LT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#else
	#define LITHE_CORE_ASSERT(...)
	#define LITHE_ASSERT(...)
#endif
