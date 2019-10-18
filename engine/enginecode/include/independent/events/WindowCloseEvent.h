#pragma once
#include "EventBaseClass.h"

class WindowCloseEvent : public EventBaseClass
{
public:
	WindowCloseEvent() {}

	EventType getEventType() const override { return EventType::WindowsClose; }
	int getCategoryFlags() const override { return EventCategoryWindow; }
};