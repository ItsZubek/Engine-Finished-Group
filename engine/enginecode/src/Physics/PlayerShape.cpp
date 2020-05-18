#include "engine_pch.h"
#include "Physics\PlayerShape.h"
#include <glad/glad.h>


namespace Engine
{

	b2Body* PlayerShape::player(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape;
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_dynamicBody;
		l_bodyDef.position.Set(position.x * PX2M, position.y * PX2M); // sets the position of the object as a parameter
		l_bodyDef.angle = orientation * DEG2RAD; // sets the direction the object is facing

		m_body = world->CreateBody(&l_bodyDef); // sets the body to appear in the world

		l_shape.SetAsBox(PX2M * size.x * 0.5f, PX2M * size.y * 0.5f);
		l_shape.m_radius = 0.0f;

		l_fixtureDef.density = m_Density; // adds mass to the shape
		l_fixtureDef.friction = m_Friction; // adds friction to the shape
		l_fixtureDef.restitution = m_Restitution; //adds bouncyness to the shape
		l_fixtureDef.shape = &l_shape; // sets fixture as the shape

		m_body->CreateFixture(&l_fixtureDef); //creates fixture
		

		return m_body;
	}

	void PlayerShape::draw(b2Vec2* points, b2Vec2 centre, float angle)
	{
		glColor3f(0.8f, 0.2f, 0.2f);

		glPushMatrix();
		glTranslatef(centre.x * M2PX, centre.y * M2PX, 0);
		glRotatef(angle * RAD2DEG, 0, 0, 1);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++)
		{
			glVertex2f(points[i].x * M2PX, points[i].y * M2PX);
		}
		glEnd();
		glPopMatrix();

		/*b2Vec2 pos;
		pos = m_body->GetPosition();
		glTranslatef(pos.x * M2PX, pos.y * M2PX, 0);
		glBegin(GL_QUADS);
		glVertex2f(2.5f, -1.5f);
		glVertex2f(1.5f, -1.5f);
		glVertex2f(1.5f, -1.4f);
		glVertex2f(2.5f, -1.4f);
		glEnd();*/

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
