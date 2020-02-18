#include "..\..\include\independent\platform\OpenGL\OpenGLShader.h"
#include "engine_pch.h"

namespace Engine
{

	void Engine::OpenGLShader::Bind() const
	{
	}

	void Engine::OpenGLShader::UnBind() const
	{
	}

	void Engine::OpenGLShader::UploadUniformMat4(const std::string & name, const glm::mat4 & matrix)
	{
	}

	void Engine::OpenGLShader::uploadFloat3(const std::string & name, float a, float b, float c)
	{
	}

	void Engine::OpenGLShader::uploadInt(const std::string & name, int data)
	{
	}
}
