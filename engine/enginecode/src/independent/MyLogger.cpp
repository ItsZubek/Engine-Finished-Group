#include "engine_pch.h"
#include "systems/MyLogger.h"



std::shared_ptr<spdlog::logger> MyLogger::s_logger;

void MyLogger::log(const std::string& msg)
{
	s_logger->info(msg);
}
//bool MyLogger::isRunning()
//{
	//return running;
//}