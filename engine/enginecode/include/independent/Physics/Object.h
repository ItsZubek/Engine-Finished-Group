#pragma once

#include <Box2D/Box2D.h>

#include "platform/OpenGL/OpenGLBuffer.h"
#include "platform/OpenGL/OpenGLShader.h"

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

//#define PX2M 1 / 60 //0.0002645833f
//#define M2PX 60 //3779.5280352161f


namespace Engine
{
	class Object
	{
	protected:
		glm::mat4 FCmodel;

		std::shared_ptr<VertexArray> m_VAO; //!< Vertex Array
		std::shared_ptr<VertexBuffer> m_VBO; //!< Vertex Buffer
		std::shared_ptr<IndexBuffer> m_IBO; //!< Index Buffer
		std::shared_ptr<Shader> m_Shader; //!< Shader

		b2Body* m_body = nullptr; //!< Box2D body, used by objects to update things like position
		float m_Density = 1.0f; //!< used to give mass
		float m_Friction = 0.4f; //!< friction used to slow objects down 
		float m_Restitution = 0.6f; //!< bouncyness of stuff
	public:
		void setUserData(void* data) { m_body->SetUserData(data); }; //!< \fn Set the user data of the body
	};
}