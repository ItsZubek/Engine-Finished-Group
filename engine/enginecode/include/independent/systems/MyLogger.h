#pragma once
#include "system.h"
#include <memory>
#include <string>
#include "spdlog/spdlog.h"

class MyLogger
{
private:
	static std::shared_ptr<spdlog::logger> s_logger;
	static bool running;

public:
	MyLogger();
	static void log(const std::string& msg);
	static bool isRunning() { return running; };
	
};