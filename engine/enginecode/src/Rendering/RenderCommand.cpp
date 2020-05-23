
#include "engine_pch.h"
#include "windows/Renderer.h"
#include "systems/MyLogger.h"

#include "Rendering\RenderCommand.h"
#include "platform/OpenGL/Rendering/OpenGLClearDepthColourBufferCommand.h"
#include "platform/OpenGL/Rendering/OpenGLSetClearColourCommand.h"
#include "platform/OpenGL/Rendering/OpenGLSetDepthTestLessCommand.h"
#include "platform/OpenGL/Rendering/OpenGLSetBackFaceCullingCommand.h"

namespace Engine
{
	RenderCommand* RenderCommand::ClearDepthColourBufferCommand()
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL("Lack of Graphics API not Supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLClearDepthColourBufferCommand();
		}
	}
	RenderCommand* RenderCommand::SetClearColourCommand(float r, float g, float b, float a)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL("Lack of Graphics API not Supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLSetClearColourCommand(r,g,b,a);
		}
	}
	RenderCommand* RenderCommand::SetDepthTestLessCommand(bool enabled)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL("Lack of Graphics API not Supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLSetDepthTestLessCommand(enabled);
		}
	}
	RenderCommand* RenderCommand::SetBackFaceCullingCommand(bool enabled)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL("Lack of Graphics API not Supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLSetBackFaceCullingCommand(enabled);
		}
	}
}