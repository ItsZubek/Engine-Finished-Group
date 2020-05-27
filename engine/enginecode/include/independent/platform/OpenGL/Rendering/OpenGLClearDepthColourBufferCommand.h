#pragma once

#include "Rendering/RenderCommand.h"

namespace Engine
{
	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private:

	public:
		OpenGLClearDepthColourBufferCommand() {};
		void action() override;

	};
}