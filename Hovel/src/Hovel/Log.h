#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // enable proprietary type logging

namespace Hovel {
	
	class HOVEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger(){return s_CoreLogger;	}	
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define HV_CORE_TRACE(...)			::Hovel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HV_CORE_INFO(...)			::Hovel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HV_CORE_WARN(...)			::Hovel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HV_CORE_ERROR(...)			::Hovel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HV_CORE_CRITICAL(...)		::Hovel::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HV_TRACE(...)			::Hovel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HV_INFO(...)			::Hovel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HV_WARN(...)			::Hovel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HV_ERROR(...)			::Hovel::Log::GetClientLogger()->error(__VA_ARGS__)
#define HV_CRITICAL(...)		::Hovel::Log::GetClientLogger()->critical(__VA_ARGS__)

