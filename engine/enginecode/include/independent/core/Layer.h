#pragma once

#include <string>
#include "events/EventBaseClass.h"

namespace Engine
{
	class Layer
	{
	protected:
		std::string m_name;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent() {}
		
		inline const std::string& GetName() const { return m_name; }
	};
}