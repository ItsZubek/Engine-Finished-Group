/** \file Renderer.cpp
*/
#include "engine_pch.h"
#include "windows/Renderer.h"
#include "include/independent/platform/OpenGL/OpenGLRendering.h"

namespace Engine {

	Renderer::RendererAPI Renderer::s_RendererAPI = Renderer::RendererAPI::OpenGL;

	
	Renderer * Renderer::createRenderer2D()
	{
		switch (RendererAPI::getApi())
		{
		case RendererAPI::API::None:
			ENGINE_FATAL("Lack of graphics API not supported.")
				break;
		case RendererAPI::API::OpenGL:
			return new OpenGLRendering();
			break;
		case RendererAPI::API::Direct3D:
			ENGINE_FATAL("Direct3D not supported.")
				break;
		default:
			ENGINE_FATAL("Unknown graphics API")
		}
	}

}