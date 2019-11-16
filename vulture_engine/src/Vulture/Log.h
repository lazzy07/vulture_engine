#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Vulture {
	class VULTURE_API Log
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

//Core log macros
#define VUL_CORE_TRACE(...)   ::Vulture::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VUL_CORE_INFO(...)    ::Vulture::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VUL_CORE_WARN(...)    ::Vulture::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VUL_CORE_ERROR(...)   ::Vulture::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VUL_CORE_FATAL(...)   ::Vulture::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define VUL_TRACE(...)        ::Vulture::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VUL_INFO(...)         ::Vulture::Log::GetClientLogger()->info(__VA_ARGS__)
#define VUL_WARN(...)         ::Vulture::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VUL_ERROR(...)        ::Vulture::Log::GetClientLogger()->error(__VA_ARGS__)
#define VUL_FATAL(...)        ::Vulture::Log::GetClientLogger()->critical(__VA_ARGS__)


