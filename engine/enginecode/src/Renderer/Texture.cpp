#include "engine_pch.h"
#include "windows/Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "platform/OpenGL/OpenGLTexture.h"
#include "windows/Renderer.h"


namespace Engine
{
	Texture* Texture::createFromFile(const std::string& filepath)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			 ENGINE_CORE_CRITICAL("Lack if graphics API not supported.");
		}
		else if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
#ifdef NG_PLATFORM_WINDOWS
			return new OpenGLTexture(filepath);
#endif // NG_PLATFORM_WINDOWS
		}
	}

	Texture* Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char* textData)
	{
		if (Renderer::GetAPI() == Renderer::RendererAPI::None)
		{
			 ENGINE_CORE_CRITICAL("Lack if graphics API not supported.");
		}
		else if (Renderer::GetAPI() == Renderer::RendererAPI::OpenGL)
		{
#ifdef NG_PLATFORM_WINDOWS
			return new OpenGLTexture(width, height, channels, textData);
#endif // NG_PLATFORM_WINDOWS
		}
	}
}
