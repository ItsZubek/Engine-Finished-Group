#include "engine_pch.h"

#include "Physics/EnemyShape.h"
#include <glad/glad.h>

namespace Engine
{
	void EnemyShape::enemy(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
	{
		b2BodyDef l_bodyDef; // defines the body
		b2PolygonShape l_shape; // Defines the shape
		b2FixtureDef l_fixtureDef; // sets the fixture of the shape

		l_bodyDef.type = b2_staticBody;
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
		
	}

	void EnemyShape::draw(b2Vec2 vertices, b2Vec2 centre, float angle)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(centre.x * M2PX, centre.y * M2PX, 0);
		glRotatef(angle * DEG2RAD, 0, 0, 1);
		glPopMatrix();
		glBegin(GL_QUADS);
		for (int i = 4; i < 4; i++)
		{
			glVertex2f(vertices.x * M2PX, vertices.y * M2PX);
		}
		glEnd();
		glPopMatrix();
	}

	void EnemyShape::Destroy()
	{
		
	}
}