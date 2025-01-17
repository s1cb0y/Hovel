#pragma once

#include <memory>

#ifdef HV_PLATFORM_WINDOWS
#if HV_DYNAMIC_LINK
	#ifdef HV_BUILD_DLL
		#define HOVEL_API __declspec(dllexport)
	#else
		#define HOVEL_API __declspec(dllimport)
	#endif
#else
	#define HOVEL_API
#endif
#else
	#error Hovel only supports windows!
#endif 

#ifdef HV_DEBUG
	#define HV_ENABLE_ASSERTS
#endif

#ifdef HV_ENABLE_ASSERTS
	#define HV_CORE_ASSERT(x, ...) if (!(x)){HV_CORE_ERROR(__VA_ARGS__); __debugbreak();}
	#define HV_ASSERT(x, ...) if (!(x)){HV_ERROR(__VA_ARGS__); __debugbreak();}
#else
	#define HV_CORE_ASSERT(x, ...)	
	#define HV_ASSERT(x, ...)	
#endif

#define BIT(x) (1 << x)

#define HV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hovel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

