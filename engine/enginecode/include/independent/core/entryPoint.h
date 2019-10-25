/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"
#include "systems/MyLogger.h"

extern Engine::Application* Engine::startApplication();

int main(int argc, char** argv)
{	
	Engine::MyLogger::Init();
	ENGINE_CORE_CRITICAL("This is a warning!");
	auto application = Engine::startApplication();
	application->run();
	delete application;


	
}

