#pragma once
#include "system.h"
#include <memory>
#include <string>
#include "spdlog/spdlog.h"
namespace Engine {


	class MyLogger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static bool running;

	public:
		static void Init();
		static void log(const std::string& msg);
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static bool isRunning() { return running; };

	};
}
//ENGINE MACROS

#define ENGINE_CORE_ERROR(...)    ::Engine::MyLogger::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)     ::Engine::MyLogger::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)     ::Engine::MyLogger::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...)    ::Engine::MyLogger::GetCoreLogger()->critical(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...)    ::Engine::MyLogger::GetCoreLogger()->trace(__VA_ARGS__)