#pragma once

#include "Object.h"

namespace Engine
{
	class EnemyShape : public Object
	{
	public:
		EnemyShape() {}; //!< Default Constructor
		b2Body* Enemy(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation); //!< Complete Constructor)
		void draw(b2Vec2* points, b2Vec2 position, float angle); //!< draws the shape
		void Destroy(); //!< destroys the enemy
	};
}