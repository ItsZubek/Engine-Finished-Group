
#include "engine_pch.h"
#include "Physics/BulletShape.h"
#include <glad/glad.h>

namespace Engine
{
	BulletShape::BulletShape(b2World* world, const glm::vec2& position, const glm::vec2& size, const float& orientation, const glm::vec3& colour)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape;
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_dynamicBody;
		l_bodyDef.position.Set(position.x, position.y); // sets the position of the object as a parameter
		l_bodyDef.angle = orientation * DEG2RAD; // sets the direction the object is facing


		m_body = world->CreateBody(&l_bodyDef); // sets the body to appear in the world
		m_body->SetUserData(this); // used by our collision listener

		l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
		l_shape.m_radius = 0.0f;

		l_fixtureDef.density = 100; // adds mass to the shape
		l_fixtureDef.friction = m_Friction; // adds friction to the shape
		l_fixtureDef.restitution = m_Restitution; //adds bouncyness to the shape
		l_fixtureDef.shape = &l_shape; // sets fixture as the shape

		m_body->CreateFixture(&l_fixtureDef); //creates fixture

		float FCvertices[6 * 4] = {
		-0.5f, -0.5f, -0.5f, colour.x, colour.y, colour.z, // red square
		 0.5f, -0.5f, -0.5f, colour.x, colour.y, colour.z,
		 0.5f,  0.5f, -0.5f, colour.x, colour.y, colour.z,
		-0.5f,  0.5f, -0.5f, colour.x, colour.y, colour.z
		};



		// Intiating the Vertex Array
		m_VAO.reset(VertexArray::create());

		// Initiating the Vertex Buffer 
		m_VBO.reset(VertexBuffer::Create(FCvertices, sizeof(FCvertices)));


		// Initiating the Buffer Layout
		Engine::BufferLayout BufferLayout = { { ShaderDataType::Float3 }, { ShaderDataType::Float3 } };

		// Adds the Buffer Layout to the Vertex Buffer
		m_VBO->setBufferLayout(BufferLayout);

		//Sets the Buffer Layout
		m_VAO->setVertexBuffer(m_VBO);

		unsigned int indices[3 * 2] = {
			2, 1, 0,
			0, 3, 2,
		};

		// Initiating the Index Buffer 
		m_IBO.reset(IndexBuffer::Create(indices, 3 * 2));
		m_IBO->Bind();
		m_VAO->setIndexBuffer(m_IBO);

		// Initiating the Shader
		m_Shader.reset(Shader::create("assets/shaders/flatColour.glsl"));
		m_Shader->Bind();

		m_bulletModel = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 3)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
	}

	void BulletShape::draw(glm::mat4 projection, glm::mat4 view)
	{
		glm::mat4 MVP = projection * view * m_bulletModel;

		//Binds the Shader and Vertex Array for Flat Colour
		m_Shader->Bind();
		m_VAO->bind();

		// Uploads the Flat Colour Uniform to the Shader
		m_Shader->UploadUniformMat4("u_MVP", &MVP[0][0]);


		glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void BulletShape::update()
	{
		b2Vec2 pos = m_body->GetPosition(); // updates body position 
		m_bulletModel = glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 3)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 1));

		// If bullet is off screen stop it from moving
		if (pos.y > 3.0f)
		{
			m_body->SetLinearVelocity(b2Vec2(0, 0));
		}
	}

	void BulletShape::fire(b2Vec2 movement)
	{
		m_bulletFired = true;
		m_body->ApplyLinearImpulseToCenter(movement, true);

		if (m_bulletCounter > 10)
		{
			m_body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			m_body->SetTransform(b2Vec2(5.0f, 0.f), 0);
		}
	}
	void BulletShape::Fired()
	{
		m_bulletFired = false;
	}

	void BulletShape::setPosition(b2Vec2 position)
	{
		m_body->SetTransform(b2Vec2(position.x, position.y), 0);

		
	}

	
}