#pragma once

#include <memory>


#ifdef CN_ENABLE_ASSERTS
	#define CN_ASSERT(x, ...) {if(!(x)) { CN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CN_CORE_ASSERT(x, ...) {if(!(x)) { CN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CN_ASSERT(x, ...)
	#define CN_CORE_ASSERT(x, ...) 
#endif


#define BIT(x) (1 << x )


#define	CN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Crimson {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;


	template<typename T, typename ... Args>
	constexpr Scope<T> MakeScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T, typename... Args>
	constexpr Ref<T> MakeRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}


}