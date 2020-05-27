#pragma once

#include "windows/Material.h"

namespace Engine
{
	class OpenGLMaterial : public Material
	{
	private:
		std::shared_ptr<Shader> m_shader; //!< shader
		std::shared_ptr<VertexArray> m_geometry; //!< vertex array
		std::map<std::string, void*> m_data; //!< the data
	public:
		OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VertexArray); //!< Initalise the shader and vertex array

		void setShader(const std::shared_ptr<Shader>& shader) override; //!< set the shader
		void setGeomerty(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;
		void setDataBlock(const std::map<std::string, void*>& data) override; //!< set a block of data as the per draw data
		void setDataElement(const std::string& dataName, void* data) override; //!< set a single uniform

		void DrawRectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour) override; //!< draws a rectangle
	
		inline std::shared_ptr<Shader> getShader() override { return m_shader; }
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& getGeometry() override
		{return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geometry);}
		inline std::map<std::string, void*> getData() override { return m_data; }
	};

}