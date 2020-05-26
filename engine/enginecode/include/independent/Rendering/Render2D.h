#pragma once

#include "windows/OrthographicCamera.h"
#include "windows/Buffer.h"
#include "windows/Shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	class Render2D
	{
	private:
		
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_vertexArray;
	public:
		 void init();
		 void shutdown();

		 void BeginScene(const OrthographicCamera& camera);
		 void EndScene();

		//primatives
		/* void DrawQuad(const glm::vec3& position, const glm::vec2& size, glm::vec4& colour); //!< Draw 3D
		 void DrawQuad(const glm::vec2& position, const glm::vec2& size, glm::vec4& colour); //!< Draw 2D*/
	};
}