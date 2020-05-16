#pragma once

#include "Object.h"

namespace Engine
{

	class BulletShape : public Object
	{
	public:
		BulletShape() {}; //!< Default Constructor
		void bullet(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation); //!< Complete Constructor
		void update(); //!< updates the position of the bullet
		void draw(b2Vec2 vertices, b2Vec2 centre, float angle); //!< Draws the bullet shape
		void movement(b2Vec2 movement); //!< moves the bullet Shape
	};
}