#pragma once

#include "Rendering.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		virtual void action() = 0;

		RenderCommand* ClearDepthColourBufferCommand();
		RenderCommand* ClearColourCommand(float r, float g, float b, float a);
		RenderCommand* SetDepthTestLessCommand(bool enabled);
		RenderCommand* SetBackFaceCullingCommand(bool enabled);
	};
}