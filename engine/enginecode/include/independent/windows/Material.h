#pragma once

#include "windows/Shader.h"
#include "windows/Buffer.h"
#include <variant>
#include <map>

namespace Engine
{
	class Material
	{
	private:

	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0; //!< set the shader
		virtual void setGeomerty(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0;
		virtual void setDataBlock(const std::map<std::string, void*>& data) = 0; //!< set a block of data as the per draw data
		virtual void setDataElement(const std::string& dataName, void* data) = 0; //!< set a single uniform#

		virtual void DrawRectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour) = 0;

		virtual std::shared_ptr<Shader> getShader() = 0;
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& getGeometry() = 0; //!< get the geometry
		virtual std::map<std::string, void*> getData() = 0;

		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
		static Material* create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& vertexBuffer);

	};
}