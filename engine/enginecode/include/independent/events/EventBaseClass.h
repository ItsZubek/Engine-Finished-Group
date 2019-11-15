#pragma once

#include <functional>

namespace Engine {
	enum class EventType
	{
		None = 0,
		WindowsClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0, //00000001
		EventCategoryInput = 1 << 1,  //00000010
		EventCategoryKeyboard = 1 << 2, //00000100
		EventCategoryMouse = 1 << 3, //00001000
		EventCategoryMouseButton = 1 << 4 //00010000
	};

	class EventBaseClass
	{
	private:
		bool m_handled = false;

	public:
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int getCategoryFlags() const = 0; //!< Get the event category
		inline bool Handled(bool IsHandled) { return m_handled; } //!< Has the event been handled
		inline void handle(bool ToHandle) { ToHandle = m_handled; } //!< handle the event
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; } //!< Is this event in the category
	};
	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(EventBaseClass& event) : m_event(event)
		{
		}
		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		EventBaseClass& m_event;
	};
}