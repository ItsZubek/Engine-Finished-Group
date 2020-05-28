#pragma once
/** \file EventBaseClass.h
*/

#include <functional>
#include <string>

namespace Engine {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
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
/**
\class EventBaseClass 
Provides a base for all events taking place
*/

	class EventBaseClass
	{
	private:
		bool m_handled = false; //!< Event Handler

	public:
		virtual EventType getEventType() const = 0; //!< Get the event type
		virtual int getCategoryFlags() const = 0; //!< Get the event category
		virtual const char* GetName() const = 0; //!< Gets the name of an event
		inline bool handled() const { return m_handled; } //!< Has the event been handled
		inline void handle(bool IsHandle) { IsHandle = m_handled; } //!< handle the event
		inline bool isInCategory(EventCategory category) { return getCategoryFlags() & category; } //!< Is this event in the category
		virtual std::string ToString() const { return GetName(); } //!< Converts to string
	};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() {return EventType::##type;}\
							   virtual EventType getEventType() const override {return getStaticType();}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category;}

	/**
\class EventDispatcher
Dispatches all events
*/
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