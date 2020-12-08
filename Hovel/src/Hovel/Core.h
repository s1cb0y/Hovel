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