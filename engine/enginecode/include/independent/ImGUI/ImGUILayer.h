#pragma once

#include "Layer/Layer.h"

namespace Engine
{
	class IMGUILayer : public Layer
	{
	public:
		IMGUILayer();
		~IMGUILayer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(float timestep);
		virtual void OnEvent(EventBaseClass& e);
	private:

	};
}
