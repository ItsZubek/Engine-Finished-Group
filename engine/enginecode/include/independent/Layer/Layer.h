#pragma once

#include "events/EventBaseClass.h"
namespace Engine
{
	class Layer
	{
	protected:
		std::string m_Name;
	public:
		Layer(std::string& name);
		~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnEvent(EventBaseClass& event) {}

		inline const std::string& GetName() const { return m_Name; }
	};
}
