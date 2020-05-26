#pragma once

#include "windows/Shader.h"
#include "windows/ShaderDataType.h"
#include "windows/Buffer.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		OpenGLShader(const std::string& filepath);

		void Bind() const override;
		void UnBind() const override;

		void setUniformMat4(const std::string& name, glm::mat4 matrix) override;
		void setUniformFloat3(const std::string& name, float a, float b, float c) override;
		void setUniformFloat4(const std::string& name, const glm::vec4& value) override;

		void UploadUniformMat4(const std::string& name, float* data) override;
		void UploadFloat4(const std::string& name, const glm::vec4& data) override;
		void uploadFloat3(const std::string& name, float a, float b, float c) override;
		void uploadInt(const std::string& name, int data) override;

		void dispatchUniformUpload(ShaderDataType type, GLuint location, void* data);
		BufferLayout getBufferLayout() const { return m_layout; } //!< gets the buffer layout for the shader

		void compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);

		virtual uint32_t getRenderedID() const override { return m_RendererID; }
	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};
}