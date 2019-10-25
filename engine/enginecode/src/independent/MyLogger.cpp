#include "engine_pch.h"
#include "systems/MyLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Engine 
{

	std::shared_ptr<spdlog::logger> MyLogger::s_CoreLogger;

	void MyLogger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);
	}

}