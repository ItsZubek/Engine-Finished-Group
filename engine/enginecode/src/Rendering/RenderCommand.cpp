
#include "engine_pch.h"
#include "Rendering\RenderCommand.h"
#include "windows/Renderer.h"
#include "systems/MyLogger.h"

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
	RenderCommand* RenderCommand::ClearColourCommand(float r, float g, float b, float a)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL("Lack of Graphics API not Supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLClearColourCommand(float r, float g, float b, float a);
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
			return new OpenGLSetDepthTestLessCommand(bool enabled);
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
			return new OpenGLSetBackFaceCullingCommand(bool enabled);
		}
	}
}