#include "engine_pch.h"

#include "Physics/EnemyShape.h"
#include <glad/glad.h>

namespace Engine
{
	b2Body* EnemyShape::Enemy(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation)
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

		return m_body;
	}

	void EnemyShape::draw(b2Vec2* points, b2Vec2 position, float angle)
	{
		glColor3f(0.8f, 0.2f, 0.2f);
		position = m_body->GetPosition();
		glPushMatrix();
		glTranslatef(position.x * M2PX, position.y * M2PX, 0);
		glRotatef(angle * RAD2DEG, 0, 0, 1);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++)
		{
			glVertex2f(points[i].x * M2PX, points[i].y * M2PX);
		}
		glEnd();
		glPopMatrix();
	}

	void EnemyShape::Destroy()
	{
		
	}
}