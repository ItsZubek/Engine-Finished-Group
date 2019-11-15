#pragma once
#include "EventBaseClass.h"

namespace Engine {
	class WindowResizeEvent : public EventBaseClass
	{
	private:
		int m_width;
		int m_height;
	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}
		static EventType getStaticType() { return EventType::WindowResize; }
		virtual EventType getEventType() const override { return EventType::WindowResize; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};

	class WindowCloseEvent : public EventBaseClass
	{
	public:
		WindowCloseEvent() {}

		static EventType getStaticType() { return EventType::WindowsClose; }
		EventType getEventType() const override { return EventType::WindowsClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};
}