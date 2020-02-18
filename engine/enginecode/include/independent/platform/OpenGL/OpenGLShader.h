#pragma once

#include "windows/Shader.h"
#include ""

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		OpenGLShader(const std::string& filepath);

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;
		virtual void uploadFloat3(const std::string& name, float a, float b, float c) override;
		virtual void uploadInt(const std::string& name, int data) override;

		void dispatchUniformUpload(ShaderDataType type, GLuint location, void* data);
		BufferLayout getBufferLayout() const { return m_layout; } //!< gets the buffer layout for the shader

		virtual uint32_t getRenderedID() const override { return m_RendererID; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};
}