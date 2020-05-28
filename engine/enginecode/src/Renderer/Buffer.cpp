/** \file Buffer.cpp
*/
#include "engine_pch.h"
#include "windows/Buffer.h"

#include "windows/Renderer.h"
#include "platform/OpenGL/OpenGLBuffer.h"

namespace Engine{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::RendererAPI::None: ENGINE_CORE_ERROR("API::NONE currently not supported"); return nullptr;
		case Renderer::RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);

		}

		ENGINE_CORE_CRITICAL("Unknown API!");
		return nullptr;
	}
	IndexBuffer * IndexBuffer::Create(uint32_t * indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::RendererAPI::None: ENGINE_CORE_ERROR("API::NONE currently not supported"); return nullptr;
		case Renderer::RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);

		}

		ENGINE_CORE_CRITICAL("Unknown API!");
		return nullptr;
	}

	VertexArray * VertexArray::create()
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::RendererAPI::None: ENGINE_CORE_ERROR("API::NONE currently not supported"); return nullptr;
		case Renderer::RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
	}
}