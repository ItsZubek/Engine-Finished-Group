#pragma once

#include "Object.h"

namespace Engine
{
	class EnemyShape : public Object
	{
	public:
	EnemyShape() {} //!< Default Constructor
	EnemyShape(b2World* world, const b2Vec2& position, const b2Vec2& size, float& orientation); //!< Complete Constructor
	void draw(b2Vec2 vertices, b2Vec2 centre, float angle); //!< draw the shape
	};
}