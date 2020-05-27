#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine
{
	class OpenGLSetDepthTestLessCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLSetDepthTestLessCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};
}