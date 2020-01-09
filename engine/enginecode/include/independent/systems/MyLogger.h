/** \file MyLogger.h
*/
#pragma once
#include "system.h"
#include <memory>
#include <string>
#include "spdlog/spdlog.h"
namespace Engine {

/**
\class MyLogger
Responsible for logging all actions happening during runtime
*/
	class MyLogger : public System
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger; //!< Initializes the logger from spdlog library
		static bool m_isRunning; //!< Boolean to know if the logger is running or not

	public:
		MyLogger() {};
		~MyLogger() {};
		void start(SystemSignal init = SystemSignal::None, ...) override;
		void stop(SystemSignal close = SystemSignal::None, ...) override;
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } //!< Logger getter

	};
}
//ENGINE MACROS

#define ENGINE_CORE_ERROR(...)    ::Engine::MyLogger::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)     ::Engine::MyLogger::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)     ::Engine::MyLogger::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...)    ::Engine::MyLogger::GetCoreLogger()->critical(__VA_ARGS__)
#define ENGINE_CORE_TRACE(...)    ::Engine::MyLogger::GetCoreLogger()->trace(__VA_ARGS__)