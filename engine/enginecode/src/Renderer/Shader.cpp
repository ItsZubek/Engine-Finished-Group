/** \file Shader.cpp
*/
#include "engine_pch.h"
#include "windows/Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "platform/OpenGL/OpenGLShader.h"
#include "windows/Renderer.h"

namespace Engine 
{
	Shader* Shader::create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::RendererAPI::None: ENGINE_CORE_ERROR("API::NONE currently not supported"); return nullptr;
		case Renderer::RendererAPI::OpenGL: return new OpenGLShader(filepath);

		}

		ENGINE_CORE_CRITICAL("Unknown API!");
		return nullptr;
	}
	Shader* Shader::create(std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		switch (Renderer::GetAPI())
		{
		case Renderer::RendererAPI::None: ENGINE_CORE_ERROR("API::NONE currently not supported"); return nullptr;
		case Renderer::RendererAPI::OpenGL: return new OpenGLShader(vertexFilePath, fragmentFilePath);

		}

		ENGINE_CORE_CRITICAL("Unknown API!");
		return nullptr;
	}
}