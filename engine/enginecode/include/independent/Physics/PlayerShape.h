#pragma once

#include "platform/OpenGL/OpenGLBuffer.h"
#include "platform/OpenGL/OpenGLShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Object.h"
#include <Box2D/Box2D.h>

namespace Engine
{


	class PlayerShape : public Object
	{
	private:
		b2Vec2* m_vertices; //!< Vertices of the Box2D shape
		unsigned int m_count;

		std::shared_ptr<VertexArray> m_VAO; //!< Vertex Array
		std::shared_ptr<VertexBuffer> m_VBO; //!< Vertex Buffer
		std::shared_ptr<IndexBuffer> m_IBO; //!< Index Buffer
		std::shared_ptr<Shader> m_Shader; //!< Shader

		glm::mat4 m_PlayerTranslation;
		
	public:
		PlayerShape() {}; //!< Default Constructor
		PlayerShape(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation); //!< Complete Contructor
		void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model); //!< draws the shape
		void update(); //!< updates the position of the shape
		void movement(b2Vec2 movement); //!< moves the player
		b2Body* getBody() { return m_body; }
		
	};
}