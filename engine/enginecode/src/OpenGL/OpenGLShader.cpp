#include "engine_pch.h"
#include "..\..\include\independent\platform\OpenGL\OpenGLShader.h"


namespace Engine
{

	void OpenGLShader::Bind() const
	{
	}

	void OpenGLShader::UnBind() const
	{
	}

	void OpenGLShader::UploadUniformMat4(const std::string & name, const glm::mat4 & matrix)
	{
	}

	void OpenGLShader::uploadFloat3(const std::string & name, float a, float b, float c)
	{
	}

	void OpenGLShader::uploadInt(const std::string & name, int data)
	{
	}
}
