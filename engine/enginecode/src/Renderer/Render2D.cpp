
#include "engine_pch.h"
#include "Rendering/Render2D.h"

namespace Engine
{
	void Render2D::init()
	{

	}
	void Render2D::shutdown()
	{
		
	}
	/*void Render2D::BeginScene(const OrthographicCamera& camera)
	{
		//glm::mat4 viewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_shader->Bind();
		m_shader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Render2D::EndScene()
	{

	}
	void Render2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, glm::vec4& colour)
	{
		m_shader->Bind();
		m_shader->setUniformFloat4("u_Colour", colour);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		m_shader->setUniformMat4("u_Transform", transform);

		m_vertexArray->bind();
		glDrawElements(GL_QUADS, m_vertexArray->getDrawCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Render2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, glm::vec4& colour)
	{
		DrawQuad({position.x, position.y, 0.f }, size, colour);
	}*/
}