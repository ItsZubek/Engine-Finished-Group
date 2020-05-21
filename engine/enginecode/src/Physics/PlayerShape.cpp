#include "engine_pch.h"
#include "Physics\PlayerShape.h"
#include <glad/glad.h>


namespace Engine
{

 PlayerShape::PlayerShape(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape;
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_dynamicBody;
		l_bodyDef.position.Set(position.x, position.y); // sets the position of the object as a parameter
		l_bodyDef.angle = orientation * DEG2RAD; // sets the direction the object is facing
		

		m_body = world->CreateBody(&l_bodyDef); // sets the body to appear in the world

		l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
		l_shape.m_radius = 0.0f;

		l_fixtureDef.density = m_Density; // adds mass to the shape
		l_fixtureDef.friction = m_Friction; // adds friction to the shape
		l_fixtureDef.restitution = m_Restitution; //adds bouncyness to the shape
		l_fixtureDef.shape = &l_shape; // sets fixture as the shape

		m_body->CreateFixture(&l_fixtureDef); //creates fixture
		

		/*m_vertices = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape())->m_vertices; // Gets the vertices of the body
		m_count = ((b2PolygonShape*)m_body->GetFixtureList()->GetShape())->m_count; // Gets the indices of the body

		// Creates a VAO
		m_VAO.reset(VertexArray::create());
		m_VAO->bind();

		// Create a VBO
		m_VBO.reset(VertexBuffer::Create((float*)m_vertices, sizeof(m_vertices)));
		BufferLayout box2DBL = { (ShaderDataType::Float3), {ShaderDataType::Float3} };
		m_VBO->setBufferLayout(box2DBL);
		m_VAO->setVertexBuffer(m_VBO);

		/*m_IBO.reset(IndexBuffer::Create((unsigned int*)4, m_count));
		m_IBO->Bind();
		m_VAO->setIndexBuffer(m_IBO);

		m_Shader.reset(Shader::create("assets/shaders/texturedPhong.glsl"));
		m_Shader->Bind();*/
		
	}

	void PlayerShape::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
	{
		

		glm::mat4 MVP = projection * view * model;
		

		m_Shader->Bind();
		m_VAO->bind();

		m_Shader->UploadUniformMat4("u_MVP", &MVP[0][0]);

		m_Shader->UploadUniformMat4("u_model", &model[0][0]);

		m_Shader->uploadFloat3("u_objectColour", 0.2f, 0.8f, 0.5f);

		m_Shader->uploadFloat3("u_lightColour", 255.f, 0.0f, 0.f);

		m_Shader->uploadFloat3("u_lightPos", 1.0f, 4.0f, -6.0f);

		m_Shader->uploadFloat3("u_viewPos", 0.0f, 0.0f, -4.5f);

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, nullptr);
	}

	void PlayerShape::update()
	{
		b2Vec2 pos = m_body->GetPosition(); // updates body position
		glVertex2f(pos.x, pos.y); // sets body position to new position
		float angle = m_body->GetAngle() * RAD2DEG; // sets angle of shape
		glRotatef(angle, pos.x, pos.y, 0); //updates the rotation of the shape
	}

	void PlayerShape::movement(b2Vec2 movement)
	{
		m_body->ApplyLinearImpulseToCenter(movement, true);
	}
}
