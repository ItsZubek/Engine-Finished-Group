/** \file WindowEvents.h
*/
#pragma once
#include "EventBaseClass.h"
#include <sstream>

namespace Engine {
	/**
\class WindowResizeEvent
Handles window resize event
*/
	class WindowResizeEvent : public EventBaseClass
	{
	private:
		unsigned int m_width, m_height;
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}
		inline unsigned int getWidth() const { return m_width; }
		inline unsigned int getHeight() const { return m_height; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};
	/**
\class WindowCloseEvent
Handles window close event
*/

	class WindowCloseEvent : public EventBaseClass
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
	};
}