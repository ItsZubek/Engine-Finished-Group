#include "engine_pch.h"

#include"windows/Renderer.h"
#include "windows\Material.h"
#include "platform/OpenGL/Rendering/OpenGLMaterial.h"
#include "systems/MyLogger.h"
#include "Profiler/profiler.h"

namespace Engine
{
	Material* Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		PROFILE_SCOPE("Material::Create");
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			ENGINE_CORE_CRITICAL(" API is not supported");
		}

		if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
			return new OpenGLMaterial(shader, vertexArray);
		}
	}
}