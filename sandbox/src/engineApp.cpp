/** \file engineApp.cpp
*/
#include "engineApp.h"

#include "systems/MyTimer.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "GameLayer.h"

#include <chrono>



engineApp::engineApp()
{
	m_layerStack->PushLayer(std::make_shared<GameLayer>(GameLayer("Game Layer")));
}

engineApp::~engineApp()
{

}



Engine::Application* Engine::startApplication()
{

	return new engineApp();
}