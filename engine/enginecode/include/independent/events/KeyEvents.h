#pragma once
#include "EventBaseClass.h"
#include <sstream>

namespace Engine {

	class KeyEvents : public EventBaseClass
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; } //!< KeyCode Getter

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvents(int keycode)
			: m_KeyCode(keycode) {}
		int m_KeyCode;

		
	};
	class KeyPressedEvent : public KeyEvents
	{
	public: 
		KeyPressedEvent(int keycode, int repeatCount )
			: KeyEvents(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_RepeatCount; //!< Repeat Count
	};
	class KeyReleasedEvent : public KeyEvents
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvents(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased);
	};
}