#pragma once

#ifdef HV_PLATFORM_WINDOWS
	#ifdef HV_BUILD_DLL
		#define HV_API __declspec(dllexport)
	#else
		#define HV_API __declspec(dllimport)
	#endif
#else
	#error Hovel only supports windows!
#endif 

	