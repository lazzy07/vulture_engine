#pragma once

#ifdef VUL_PLATFORM_WINDOWS
#if VUL_DYNAMIC_LINK
	#ifdef VUL_BUILD_DLL
		#define VULTURE_API __declspec(dllexport)
	#else
		#define VULTURE_API __declspec(dllimport)
	#endif
#else
#define VULTURE_API
#endif
#else
	#error Vulture only supports windows
#endif


#ifdef VUL_DEBUG
	#define VUL_ENABLE_ASSERTS
#endif

#ifdef VUL_ENABLE_ASSERTS
	#define VUL_ASSERT(x, ...) {if(!(x)) { VUL_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
	#define VUL_CORE_ASSERT(x, ...) {if(!(x)) { VUL_ERROR("Assertion Failed {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VUL_ASSERT(x, ...) 
	#define VUL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VUL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

