/** \file Shader.h
*/
#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Engine {
	/**
\Shader class
*/
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void uploadFloat3(const std::string& name, float a, float b, float c) = 0;
		virtual void uploadInt(const std::string& name, int data) = 0;

		virtual uint32_t getRenderedID() const = 0;

		static Shader * create(const std::string& filepath);
		static Shader * create(std::string& vertexFilePath, const std::string& fragmentFilePath);
	protected:
		uint32_t m_RendererID;

	};
}