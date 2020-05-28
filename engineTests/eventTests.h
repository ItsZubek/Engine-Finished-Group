#pragma once

#include <gtest/gtest.h>
#include "events/EventBaseClass.h"
#include "events/WindowEvents.h"

const int width = 1024;
const int height = 720;

Engine::WindowResizeEvent re(width, height);
Engine::WindowCloseEvent ce;

bool onResizeTrue(Engine::WindowResizeEvent& e)
{
	return true;
}
bool onResizeFalse(Engine::WindowResizeEvent& e)
{
	return false;
}