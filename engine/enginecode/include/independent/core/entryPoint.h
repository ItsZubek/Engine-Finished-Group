/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
#include "systems/MyLogger.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{	
	auto application = Engine::startApplication();
	application->run();
	delete application;
	
	//MyLogger::log("random log test");
	return 0;
}

