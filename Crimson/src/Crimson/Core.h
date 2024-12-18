#pragma once


#ifdef CN_PLATFORM_WINDOWS
	#ifdef CN_BUILD_DLL
		#define CRIMSON_API __declspec(dllexport)
	#else
		#define CRIMSON_API __declspec(dllimport)
#endif 


#else 
	#error Crimson only supports windows!
#endif


#define BIT(x) (1 << x )