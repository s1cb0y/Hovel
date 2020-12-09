#pragma once

#ifdef HV_PLATFORM_WINDOWS
	#ifdef HV_BUILD_DLL
		#define HOVEL_API __declspec(dllexport)
	#else
		#define HOVEL_API __declspec(dllimport)
	#endif
#else
	#error Hovel only supports windows!
#endif 

#define BIT(x) (1 << x)	

#ifdef HV_ENABLE_ASSERTS
	#define HV_CORE_ASSERT(x, ...) if (!(x)){HV_CORE_ERROR(__VA_ARGS__); __debugbreak();}
	#define HV_ASSTERT(x, ...) if (!(x)){HV_ERROR(__VA_ARGS__); __debugbreak();}
#else
	#define HV_CORE_ASSERT(x, ...)	
	#define HV_ASSERT(x, ...)	
#endif
