#include "engine_pch.h"
#include "AI/ship.h"
namespace Engine
{
	
	Ship::Ship(b2World * world, const glm::vec2 & position, const glm::vec2 & size, const float & orientation, const glm::vec3 & colour)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape;
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_staticBody;
		l_bodyDef.position.Set(position.x, position.y); // sets the position of the object as a parameter
		l_bodyDef.angle = orientation * DEG2RAD; // sets the direction the object is facing


		m_body = world->CreateBody(&l_bodyDef); // sets the body to appear in the world
		m_body->SetUserData(this); // used by our collision listener

		l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
		l_shape.m_radius = 0.0f;

		l_fixtureDef.density = m_Density; // adds mass to the shape
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

		EnemyShip = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 3)) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1));
	}

	void Ship::draw(glm::mat4 projection, glm::mat4 view)
	{
		glm::mat4 MVP = projection * view * EnemyShip;

		//Binds the Shader and Vertex Array for Flat Colour
		m_Shader->Bind();
		m_VAO->bind();

		// Uploads the Flat Colour Uniform to the Shader
		m_Shader->UploadUniformMat4("u_MVP", &MVP[0][0]);


		glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Ship::movement(b2Vec2 movement, float spin)
	{
		m_body->ApplyLinearImpulseToCenter(movement, true);
		m_body->ApplyAngularImpulse(spin, true);
	}
	
	void Ship::raycast(b2World* world, b2Vec2 p1, b2Vec2 p2)
	{
		
		float rayLength = 25;
		b2Vec2 p1 = (&m_body->GetPosition); //center of scene
		b2Vec2 p2 = p1 + rayLength * b2Vec2(sinf(&m_body->GetAngle), cosf(&m_body->GetAngle));

		glColor3f(1, 1, 1); //white
		
		b2RayCastInput input;
		input.p1 = p1;
		input.p2 = p2;
		input.maxFraction = 1;

		//check every fixture of every body to find closest
		float closestFraction = 1; //start with end of line as p2
		b2Vec2 intersectionNormal(0, 0);
		for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
			for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

				b2RayCastOutput output;
				if (!f->RayCast(&output, input, 1))
					continue;
				if (output.fraction < closestFraction) {
					closestFraction = output.fraction;
					intersectionNormal = output.normal;
				}
			}
		}
		b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

		//draw this part of the ray
		glBegin(GL_LINES);
		glVertex2f(p1.x, p1.y);
		glVertex2f(intersectionPoint.x, intersectionPoint.y);
		glEnd();

		if (closestFraction == 1)
			return; //ray hit nothing so we can finish here
		if (closestFraction == 0)
			return;
		canSee = true;

	

		//recurse
		

	}
	void Ship::update()
	{
		b2Vec2 pos = m_body->GetPosition(); // updates body position 
		EnemyShip = glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 3)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.2, 1));

		if (pos.x > 4.5f)
		{
			m_body->SetTransform(b2Vec2(-4.4f, -2.5f), 0);
		}

		if (pos.x < -4.5)
		{
			m_body->SetTransform(b2Vec2(4.4f, -2.5f), 0);
		}
	}


	void Ship::goForward()
	{
		movement(b2Vec2(0.f, 0.2f), (0));
	}

	void Ship::goBackward()
	{
		movement(b2Vec2(0.f, -0.2f), (0));
	}

	void Ship::goLeft()
	{
		movement(b2Vec2(-0.2f, 0.0f), (0));
	}

	void Ship::goRight()
	{
		movement(b2Vec2(0.2f, 0.0f), (0));
	}

	void Ship::ShipRotateLeft()
	{
		movement(b2Vec2(0.0f, 0.0f), (-30));
	}

	void Ship::ShipRotateRight()
	{
		movement(b2Vec2(0.0f, 0.0f), (30));
	}

	void Ship::stop()
	{
		m_body->SetLinearVelocity(b2Vec2(0, 0));
		m_body->SetAngularVelocity(0);
	}


	void Ship::Destroy()
	{
		//m_body->DestroyFixture();
	}


	b2Vec2 Ship::EnemyPosition()
	{
		return m_body->GetPosition();
	}

}