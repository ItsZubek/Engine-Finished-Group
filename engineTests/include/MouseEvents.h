#pragma once
#include "events/MouseEvents.h"
#include <gtest/gtest.h>

using namespace Engine;

float x = 50.f;
float y = 50.f;
float xoffset = 100;
float yoffset = 100;
int button;
MouseMovedEvent mousemove(x, y);
MouseScrolledEvent mousescroll(xoffset, yoffset);
MouseButtonPressedEvent mousepress(button);
MouseButtonReleasedEvent mouserelease(button);