/** \file engineApp.cpp
*/
#include "engineApp.h"
#include "imgui.h"
#include "systems/MyTimer.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <chrono>


engineApp::engineApp()
{
	
}

engineApp::~engineApp()
{

}



Engine::Application* Engine::startApplication()
{
	
	return new engineApp();
	
}