#pragma once

#include "events/EventBaseClass.h"
namespace Engine
{
	class Layer
	{
	protected:
		std::string m_Name;
	public:
		Layer(const std::string& name);
		~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float timestep) {}
		virtual void OnEvent(EventBaseClass& e) {}

		inline const std::string& GetName() const { return m_Name; }
	};
}
