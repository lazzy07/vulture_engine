#pragma once

#ifdef VUL_PLATFORM_WINDOWS
	#ifdef VUL_BUILD_DLL
		#define VULTURE_API __declspec(dllexport)
	#else
		#define VULTURE_API __declspec(dllimport)
	#endif
#else
	#error Vulture only supports windows
#endif