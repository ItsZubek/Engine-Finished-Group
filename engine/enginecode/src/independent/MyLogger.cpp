#include "engine_pch.h"
#include "systems/MyLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine 
{

	std::shared_ptr<spdlog::logger> MyLogger::s_CoreLogger;
	bool MyLogger::m_isRunning;

	void MyLogger::start(SystemSignal init, ...)
	{
		m_isRunning = true;
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_CoreLogger->info("Logger Initialised.");
	}

	void MyLogger::stop(SystemSignal close, ...)
	{
		m_isRunning = false;
		s_CoreLogger->info("Logger Shut Down.");
	}

}