#include "engine_pch.h"

#include "Physics/EnemyShape.h"
#include <glad/glad.h>

namespace Engine
{
	EnemyShape::EnemyShape(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape; // Defines the shape
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_staticBody;
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
		
	}

	void EnemyShape::draw(b2Vec2 vertices, b2Vec2 centre, float angle)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(centre.x * m_Meters2Pixel, centre.y * m_Meters2Pixel, 0);
		glRotatef(angle * DEG2RAD, 0, 0, 1);
		glPopMatrix();
		glBegin(GL_QUADS);
		for (int i = 4; i < 4; i++)
		{
			glVertex2f(vertices.x * m_Meters2Pixel, vertices.y * m_Meters2Pixel);
		}
		glEnd();
		glPopMatrix();
	}
}