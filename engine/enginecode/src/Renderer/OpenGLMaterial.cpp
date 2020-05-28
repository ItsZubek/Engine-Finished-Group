
#include "engine_pch.h"
#include "windows/Material.h"
#include "platform\OpenGL\Rendering\OpenGLMaterial.h"

#include <glm/gtc/matrix_transform.hpp>
#include "Profiler/profiler.h"

namespace Engine
{
	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VertexArray)
	{
		PROFILE_SCOPE("OpenGLMaterial::Create");
		float FCvertices[6 * 24] = {
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f, // red square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.2f,
			-0.5f,  0.5f, -0.5f,  0.8f, 0.2f, 0.2f,
			-0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f, // green square
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f, 0.5f,  0.2f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f, // magenta(ish) square
			 0.5f, -0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			 0.5f, -0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f, 0.5f,  0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f, // yellow square 
			 0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f, 0.5f, 0.5f,  0.8f, 0.8f, 0.2f,
			-0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.8f, // Cyan(ish) square 
			-0.5f,  0.5f, -0.5f,  0.2f, 0.8f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			-0.5f,  -0.5f, 0.5f, 0.2f, 0.8f, 0.8f,
			0.5f, -0.5f, -0.5f, 0.2f, 0.2f, 0.8f, // Blue square 
			0.5f,  0.5f, -0.5f,  0.2f, 0.2f, 0.8f,
			0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.8f,
			0.5f,  -0.5f, 0.5f, 0.2f, 0.2f, 0.8f
		};

		// Intiating the Vertex Array
		VertexArray->create();

		 std::shared_ptr<VertexBuffer> vertexBuffer;

		// Initiating the Vertex Buffer 
		vertexBuffer.reset(VertexBuffer::Create(FCvertices, sizeof(FCvertices)));


		// Initiating the Buffer Layout
		BufferLayout FCBufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 } };

		// Adds the Buffer Layout to the Vertex Buffer
		vertexBuffer->setBufferLayout(FCBufferLayout);

		//Sets the Buffer Layout
		VertexArray->setVertexBuffer(vertexBuffer);

		unsigned int indices[3 * 12] = {
			2, 1, 0,
			0, 3, 2,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			14, 13, 12,
			12, 15, 14,
			18, 17, 16,
			16, 19, 18,
			20, 21, 22,
			22, 23, 20
		};


		std::shared_ptr<IndexBuffer> indexBuffer;

		// Initiating the Index Buffer 
		indexBuffer.reset(IndexBuffer::Create(indices, 3 * 12));
		indexBuffer->Bind();
		VertexArray->setIndexBuffer(indexBuffer);

		// Initiating the Shader
		shader->create("assets/shaders/boxShape.glsl");
		shader->Bind();
	}
	void OpenGLMaterial::DrawRectangle(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		m_shader->Bind();
		m_shader->setUniformFloat4("u_Colour", colour);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		m_shader->setUniformMat4("u_Transform", transform);

		m_geometry->bind();
		glDrawElements(GL_QUADS, m_geometry->getDrawCount(), GL_UNSIGNED_INT, nullptr);

	}
	/*void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();

	}
	void OpenGLMaterial::setGeomerty(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{

	}
	void OpenGLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{

	}
	void OpenGLMaterial::setDataElement(const std::string& dataName, void* data)
	{

	}*/

}