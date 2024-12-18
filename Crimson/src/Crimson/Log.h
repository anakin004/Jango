#pragma once


#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

// Logger for Crimson 
   /*

   Rather than just using prints, its way better to have colors and
   formatting for logging and debugging, setting loglevels, etc

   */
namespace Crimson {

	class CRIMSON_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};



}


// add define for distro build vs prod
/*
 like #ifdef CN_DST
			#define CN_...(...) ::Crimson::Log::GetCoreLogger...
					...
	  #else
			#define CN_...(...) 
*/

/*
We dont neccesarrily need these wrappers, but using them makes the api more Crimson-Engine specific
*/

// core logging macros
#define CN_CORE_TRACE(...)   ::Crimson::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define CN_CORE_INFO(...)    ::Crimson::Log::GetCoreLogger()->info(__VA_ARGS__);
#define CN_CORE_WARN(...)    ::Crimson::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define CN_CORE_ERROR(...)   ::Crimson::Log::GetCoreLogger()->error(__VA_ARGS__);
#define CN_CORE_CRITICAL(...)   ::Crimson::Log::GetCoreLogger()->critical(__VA_ARGS__);

// client logging macros
#define CN_TRACE(...)   ::Crimson::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CN_INFO(...)    ::Crimson::Log::GetClientLogger()->info(__VA_ARGS__);
#define CN_WARN(...)    ::Crimson::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CN_ERROR(...)   ::Crimson::Log::GetClientLogger()->error(__VA_ARGS__);
#define CN_CRITICAL(...)   ::Crimson::Log::GetClientLogger()->critical(__VA_ARGS__);