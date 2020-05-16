#pragma once

#include "Object.h"
#include <Box2D/Box2D.h>

namespace Engine
{


	class PlayerShape : public Object
	{
	public:
		PlayerShape() {}; //!< Default Constructor
		b2Body* player(b2World* world, const b2Vec2& position, const b2Vec2& size, const float& orientation);
		void draw(b2Vec2* points, b2Vec2 centre, float angle); //!< draws the shape
		void update(); //!< updates the position of the shape
		void movement(b2Vec2 movement); //!< moves the player
		b2Body* getBody() { return m_body; }
	};
}