
#include "engine_pch.h"
#include "Physics/BulletShape.h"
#include <glad/glad.h>

namespace Engine
{
	BulletShape::BulletShape(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape; // Defines the shape
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_dynamicBody;
		l_bodyDef.position.Set(position.x * m_Pixel2Meters, position.y * m_Pixel2Meters); // sets the position of the object as a parameter
		l_bodyDef.angle = orientation * DEG2RAD; // sets the direction the object is facing

		m_body = world->CreateBody(&l_bodyDef); // sets the body to appear in the world

		l_shape.SetAsBox(m_Pixel2Meters * size.x * 0.5f, m_Pixel2Meters * size.y * 0.5f);
		l_shape.m_radius = 0.0f;

		l_fixtureDef.density = m_Density; // adds mass to the shape
		l_fixtureDef.friction = m_Friction; // adds friction to the shape
		l_fixtureDef.restitution = m_Restitution; //adds bouncyness to the shape
		l_fixtureDef.shape = &l_shape; // sets fixture as the shape

		m_body->CreateFixture(&l_fixtureDef); //creates fixture
		m_body->SetLinearDamping(0.2f); // adds movement to the body
	}

	void BulletShape::draw(b2Vec2 vertices, b2Vec2 centre, float angle)
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslatef(centre.x * m_Meters2Pixel, centre.y * m_Meters2Pixel, 0);
		glRotatef(angle * DEG2RAD, 0, 0, 1);
		glPopMatrix();
		glBegin(GL_QUADS);
		for (int i = 4; i < 4; i++)
		{
			glVertex2f(vertices[i].x * m_Meters2Pixel, vertices[i].y * m_Meters2Pixel);
		}
		glEnd();
		glPopMatrix();
	}

	void BulletShape::update()
	{
		b2Vec2 pos = m_body->GetPosition(); // updates body position
		glVertex2f(pos.x, pos.y); // sets body position to new position
		float angle = m_body->GetAngle() * RAD2DEG; // sets angle of shape
		glRotatef(angle, pos.x, pos.y, 0); //updates the rotation of the shape
	}

	void BulletShape::Movement(b2Vec2 movement)
	{
		m_body->ApplyLinearImpulseToCenter(movement, true);
	}
}