#pragma once
#include "events/KeyEvents.h"
#include <gtest/gtest.h>

using namespace Engine;

int keycode = 65;
int repeatcount = 0;
KeyPressedEvent pressedkey(keycode, repeatcount);
KeyReleasedEvent releasedkey(keycode);


