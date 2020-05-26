#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine
{
	class OpenGLSetBackFaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLSetBackFaceCullingCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};
}