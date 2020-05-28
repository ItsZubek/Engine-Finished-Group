#pragma once
#include "events/WindowEvents.h"
#include <gtest/gtest.h>

using namespace Engine;


unsigned int width = 800;
unsigned int height = 600;
WindowResizeEvent windowresizeevent(width, height);
WindowCloseEvent closeevent;
