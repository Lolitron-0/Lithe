/*****************************************************************//**
 * \file   Core.hpp
 * \brief  Main macros defines
 * 
 * \author Lolitron
 * \date   May 2023
 *********************************************************************/
#pragma once

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_DLL
		#define LITHE_API __declspec(dllexport)
	#else
		#define LITHE_API __declspec(dllimport)
	#endif
#else
	#error Lithe only supports Windows
#endif

#define BIT(x) (1<<x)